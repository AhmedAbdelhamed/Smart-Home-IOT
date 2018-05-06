<?php include 'connect.php' ; ?>
<?php
   		
	  /*
	    when this variable is set data coming from request will be stored in database
	  */
	  $update_server_value="";
	      
	  /*
      send this when requesting from micro-controller :
	  192.168.1.8/ha1/wb/electro.php?unit=1&led=1&fan=1&heater=1&temp=25&update_server_value=1  
		
	  //and then server will send back this in the current page 'elector.php':
	  -LED#1#LED-FAN#1#FAN-HEATER#1#HEATER-TEMP#25#TEMP-UPDATE_SERVER_VALUE#1#UPDATE_SERVER_VALUE
  
     */	 
		
		//using loop to get value passed in URL from micro-controller
		foreach($_REQUEST as $key => $value)  
		{
			//if unit is found, get its value
			if($key =="unit")
			{
				$unit = $value;
			}

			//if temp is found, get its value, store it in database
			if($key =="temp")
			{
			   $temp = $value;
		       mysqli_query($con,"UPDATE table1 SET TEMP = $temp WHERE id=$unit");
			}
					
			//if update_server_value is found, get its value 
			if($key == "update_server_value")
			{
				$update_server_value  = $value; 
			}
			//if led value send is found, get its value 
			if($key =="led")
			{
				$led = $value;
			}

			//if fan is found, get its value
			if($key =="fan")
			{
				$fan = $value;
			}
			
			//if heater is found, get its value
			if($key =="heater")
			{
				$heater = $value;
			}
		}

 	    //if update_server_value is set update values in database
		if ($update_server_value == '1')
		{
			//update led value in database
			mysqli_query($con,"UPDATE table1 SET LED = $led WHERE id=$unit");
			//update fan value in database
			mysqli_query($con,"UPDATE table1 SET FAN = $fan WHERE id=$unit");
			//update heater value in database
			mysqli_query($con,"UPDATE table1 SET HEATER = $heater WHERE id=$unit");
		}
		
		//get all data from database and store it in $result
		$result = mysqli_query($con,"SELECT * FROM table1");
		/*
		   loop to get LED & FAN & HEATER & TEMPERATURE from database and output the values 
		   to the current page 'elector.php'.   
		*/
		while($row = mysqli_fetch_array($result))
		{
			if($row['id'] == $unit)
			{
				$get_led = $row['LED']; 
				$get_fan = $row['FAN'];
				$get_heater = $row['HEATER'];
				$get_temp = $row['TEMP']; 
		      echo "-LED#$get_led#LED-FAN#$get_fan#FAN-HEATER#$get_heater#HEATER-TEMP#$get_temp#TEMP-UPDATE_SERVER_VALUE#$update_server_value#UPDATE_SERVER_VALUE"; 
		   }
		}
?>