/*
 * esp.c
 *
 *  Created on: Oct 19, 2017
 *      Author: Ahmed
 */

#include "esp.h"

void UART_Write_AT(uint8 *str) {
	UART_sendString(str);
	new_line();
}

void new_line() {
	UART_sendByte(0x0D);
	UART_sendByte(0x0A);
}

uint8 find_string(uint8 *string, uint8 *string_find) {
	uint16 mathced = 0; //will be incremented in each matching char
	uint16 index_string = 0; //index of string source
	uint16 length_of_string = 0; //length of string source
	uint16 length_of_string_find = 0; //length of the text to be found

	length_of_string = strlen(string); //get length of string source
	length_of_string_find = strlen(string_find); //get length of the text to be found

	//return 0 if string find size is greater than string source
	if (length_of_string_find > length_of_string) {
		return 0;
	}

	for (index_string = 0; index_string < length_of_string; index_string++) //iterate until length of string source
			{
		if (string[index_string] == string_find[mathced]) //if current char is mathcing
				{
			mathced++; //increment mathced in each matching char
			if (length_of_string_find == mathced) //if found equals the size of string find
					{
				return 1; //return 1 because string is found
			}
		} else //otherwise reset mathced
		{
			mathced = 0;
		}
	}

	return 0;  //return 0 if string is not found in string source
}

//void find_get_string(char *string, char *from, char _from, char *to, char _to, char _to_sub, char *get_text)
//{
//     char *p1; //pointer to string elements
//     char *p2; //pointer to string find(from) elements in string
//     char length=0; //gets the length between the two strings
//
//    /*
//      get the location of the first occurance of string 1 in memory
//      so the location of the first value is returned.
//      add a number(_from) to point p1 next to any value from the first occurance location
//      value. so p1 is a pointer in memory to the location of first occurance of
//      string 1.
//    */
//    p1 = strstr(string, from) + _from;
//
//
//    /*
//       get the location of the first occurance of string 2 in memory
//       when sending the value of p1 the search will start from the value of
//       p1 until it finds the location of the first occurance of the string 2
//       in memory. so the location of the first value + _to is returned.
//    */
//    p2 = strstr(p1, to) + _to;
//
//    /*
//      get how many characters in between
//    */
//    length = p2 - p1;
//
//    /*
//       copy the found characters, from p1 to number of char found in between
//       last char in found char as null.
//       length -_to_sub, this means clear any char start from last char to _to_sub
//       to clear some unwanted values at the end of the string.
//    */
//    strncpy(get_text, p1, length);
//    get_text[length -_to_sub] = '\0';
//}

void find_get_string(uint8 *string, uint8 *from, uint8 _from, uint8 *to,
		uint8 _to, uint8 *get_text) {
	uint8 *p1; //pointer to string elements
	uint8 *p2; //pointer to string find(from) elements in string
	uint8 length = 0; //gets the length between the two strings

	/*
	 get the location of the first occurance of string 1 in memory
	 so the location of the first value is returned.
	 add a number(_from) to point p1 next to any value from the first occurance location
	 value. so p1 is a pointer in memory to the location of first occurance of
	 string 1.
	 */
	p1 = strstr(string, from) + _from;

	/*
	 get the location of the first occurance of string 2 in memory
	 when sending the value of p1 the search will start from the value of
	 p1 until it finds the location of the first occurance of the string 2
	 in memory. so the location of the first value + _to is returned.
	 */
	p2 = strstr(p1, to) + _to;

	/*
	 get how many characters in between
	 */
	length = p2 - p1;

	/*
	 copy the found characters, from p1 to number of char found in between
	 last char in found char as null
	 */
	strncpy(get_text, p1, length);
	get_text[length] = '\0';
}
