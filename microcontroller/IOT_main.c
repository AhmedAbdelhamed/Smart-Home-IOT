/*
 * main.c
 *
 *  Created on: Apr 1, 2018
 *      Author: ahmed
 */

#include <string.h>
#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
#include "esp.h"
#include "lcd.h"
#include "uart.h"


//wifi connections settings
const uint8 SSID[] = "IOT";
const uint8 password[] = "12341234";
const uint8 port[] = "80";

const char connect_server[] = "AT+CIPSTART=1,\"TCP\",\"192.168.43.152\",80";
char led_value[2]; //stores LED value as char to append it to the request command
char fan_value[2];   //stores FAN value as char to append it to the request command
char heater_value[2]; //stores HEATER value as char to append it to the request command
char _http_get[300]; //stores request to be sent to the web server
const char http_get[] = "GET http://192.168.43.63/projects/ha1/wb/electro.php?unit=1&led=";
char power[10] = "12.456";


//responose variabales
const uint8 OK = 1;
const uint8 ready = 2;
const uint8 no_change = 3;
const uint8 send_ready = 4;
const uint8 ERROR = 5;
const uint8 WIFI_GOT_IP = 6;
const uint8 WIFI_DISCONNECT = 7;
const uint8 WIFI_CONNECTED = 8;
const uint8 FAIL = 9;

uint8 rx_buff[500]; //stores DATA read
uint8 data_ready;  //will be set if DATA is ready in buffer
uint16 data_len; //determines the length of buffer
uint8 res;
uint8 tmp;   //tmp will store temprory received DATA(byte)




ISR(USART_RXC_vect){
	char tmp = UART_recieveByte();
	switch(tmp) //check the value of the read byte
	 {
	   case LF: //IF NEW LINE IS FOUND
		  if(data_len > 1)  //and if there is data
		  {
			data_ready = 1; //SET DATA READY FLAG
		  }
		  break;
	   case CR: //IF CARRIAGE RETURN IS FOUND
		  rx_buff[data_len] = 0; //MAKE LAST ELEMENT IN BUFFER AS NULL
		  break;
	   default:  //otherwise read DATA in buffer
			  rx_buff[data_len] = tmp;  //READ DATA IN BUFFER
			  data_len++;     //INCREMENT COUNTER TO READ NEXT BYTE
	}
}

void reset_buff()
{
  memset(rx_buff,0,data_len); //reset buffer from first index to length used

  //reset variables used with buffer
  data_ready = 0;
  data_len=0;
}

uint8 response_success()
{
  uint8 result;

  while(!data_ready); //waite until DATA buffer is ready

  if(find_string(rx_buff,"OK") == 1){result = OK;} //if "OK" is found in buffer
  else if(find_string(rx_buff,"no change") == 1){result = no_change;}//if "no change" is found
  else if(find_string(rx_buff,"ready") == 1){result = ready;}//if "ready" is found
  else if(find_string(rx_buff,">") == 1){result = send_ready;}  //ready to receive DATA ">"
  else if(find_string(rx_buff,"ERROR") == 1){result = ERROR;}  //ready to receive DATA ">"
  else if(find_string(rx_buff,"WIFI GOT IP") == 1){result = WIFI_GOT_IP;}//if "ready" is found
  else if(find_string(rx_buff,"WIFI DISCONNECT") == 1){result = WIFI_DISCONNECT;}//if "ready" is found
  else if(find_string(rx_buff,"WIFI CONNECTED") == 1){result = WIFI_CONNECTED;}//if "ready" is found
  else if(find_string(rx_buff,"FAIL") == 1){result = FAIL;}//if "ready" is found
  else result = 0; //else if other is found maybe "ERROR" or "FAIL" etc, result will be no success

  reset_buff(); //reset buffer

  return result;  //return the result of the response
}

void WiFi_Config()
{
   //reset variables
   data_ready = 0;
   data_len = 0;
   memset(rx_buff,0,500); //reset buffer, put 0 to all element of buffer

   LCD_clearScreen();
   LCD_displayStringRowColumn(0,1,"Sending AT");
   LCD_displayStringRowColumn(1,1,"Please wait...");
   UART_Write_AT("AT");   //send AT
   _delay_ms(1000);


   UART_Write_AT("AT+RST");   //Reset WiFi module using uart
   //reset_wifi(); //Reset WiFi module using PIN
   do{
	   res = response_success();
	   //(res != WIFI_GOT_IP) && (res != WIFI_DISCONNECT)
   }while(res != ready ); //wait until response success is found
   _delay_ms(3000);

   //Disconnect from any AP at the beginning
   LCD_clearScreen();
   LCD_displayStringRowColumn(0,1,"Disconnecting WIFI");
   LCD_displayStringRowColumn(1,1,"Please wait...");
   UART_Write_AT("AT+CWQAP");   //Disconnect from any AP at the beginning
   _delay_ms(1000);

   //set the working mode to 3 both station mode and AP
   LCD_clearScreen();
   LCD_displayStringRowColumn(0,1,"Setting mode");
   LCD_displayStringRowColumn(1,1,"Please wait...");
   UART_Write_AT("AT+CWMODE=3");   //select both station and access point mode
   while(response_success() != OK);   //wait until response success is found
   _delay_ms(1000);

   //Enable multiple or single connections
   LCD_clearScreen();
   LCD_displayStringRowColumn(0,1,"Setting connection");
   LCD_displayStringRowColumn(1,1,"mode");
   LCD_displayStringRowColumn(1,6,"Please wait...");
   UART_Write_AT("AT+CIPMUX=1");  //Enable multiple connection
   while(response_success() != OK); //wait until response success is found
   _delay_ms(1000);

   //infinit loop to join access point
   while(1)
   {
	 //AT+CWJAP="medo-PC","01150535088"
     LCD_clearScreen();
     LCD_displayStringRowColumn(0,1,"Connecting to AP");
     LCD_displayStringRowColumn(1,1,"Please wait...");
     UART_sendString("AT+CWJAP=");    //AT+CWJAP="SAMEER.STC","0530sameer"
     UART_sendByte('"');
     UART_sendString(SSID);
     UART_sendString("\",\"");
     UART_sendString(password);
     UART_sendByte('"');
     new_line();
     _delay_ms(2000);
     do
    	 res = response_success();
     while((res != OK) && (res != ERROR) && (res != FAIL));
     if(res == OK) //if response success is found
     {
       LCD_clearScreen();
       LCD_displayStringRowColumn(0,1,"Success");
       break;
     }
     else //if response success is not found
     {
         LCD_displayStringRowColumn(0,1,"Try again...");
       _delay_ms(1000);
     }
   }
   _delay_ms(1000);

   //test if wifi module was connected to an access point
//      LCD_clearScreen();
//      LCD_displayStringRowColumn(0,1,"Check connection");
//      LCD_displayStringRowColumn(1,1,"Please wait...");
//      while(1){
//
//   	   UART_Write_AT("AT+CWJAP?");   //check if module is connected to AP
//   	   do
//   		   res = response_success();
//      	   while((res != OK) && (res != ERROR) && (res != FAIL));
//   	   if(res == OK) break;
//   	   _delay_ms(1000);
//      }

      LCD_clearScreen();
      LCD_displayStringRowColumn(0,1,"WiFi Module Connected");
      _delay_ms(1000);

   reset_buff(); //reset first read buffer
}


void extract_data()
{

   while(!find_string(rx_buff,"CLOSED"));

   if(find_string(rx_buff,"LED#1"))
   		PORTB |=1<<0;
   else
	   PORTB &=~(1<<0);

   if(find_string(rx_buff,"FAN#1"))
   		PORTB |=1<<1;
   else
	   PORTB &=~(1<<1);

   if(find_string(rx_buff,"HEATER#1"))
   		PORTB |=1<<2;
   else
	   PORTB &=~(1<<2);


}

//this function checks for webpage request to serve it
void send_status()
{
	reset_buff();
	UART_Write_AT(connect_server);
	_delay_ms(2000);
	UART_Write_AT("AT+CIPSEND=1,115");
	_delay_ms(2000);
	reset_buff();
	                         // 192.168.43.66/ha1
	UART_sendString("GET http://192.168.43.152/ha1/wb/electro.php?unit=1&led=1&fan=1&heater=1&temp=25&update_server_value=0 HTTP/1.0\r\n\r\n");
	_delay_ms(1000);
	extract_data();

}

////this function checks for webpage request to serve it
//void send_status()
//{
//	reset_buff();
//	UART_Write_AT(connect_server);
//	_delay_ms(2000);
//	UART_Write_AT("AT+CIPSEND=1,123");
//	_delay_ms(2000);
//	reset_buff();
//	UART_sendString("GET http://192.168.43.63/projects/ha1/wb/electro.php?unit=1&led=1&fan=1&heater=1&temp=25&update_server_value=0 HTTP/1.0\r\n\r\n");
//	_delay_ms(1000);
//	extract_data();
//
//}




int main(){

	DDRB = 0xff;
	PORTB = 0xff;
	_delay_ms(1000);
	PORTB = 0x00;

	UART_init();
	SREG |= 1<<7;
	LCD_init();
	LCD_sendCommand(CURSOR_OFF);
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,1,"medo");
	_delay_ms(500);
	LCD_goToRowColumn(1,8);


	WiFi_Config();
	UART_Write_AT("AT+CIFSR");



while(1)
{
	_delay_ms(1000);
	send_status();
}



}
