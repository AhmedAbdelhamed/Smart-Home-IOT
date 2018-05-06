 
<?php include 'connect.php' ; ?>

<!--for refreshing the homepage -->
<?php 
$page = $_SERVER['PHP_SELF'];
$sec = "17";
?>
 
<html>
    <head>
       <meta http-equiv="refresh" content="<?php echo $sec?>;URL='<?php echo $page?>'">
	   <title>IoT</title>
	   <link rel="stylesheet" href="css/style.css" type="text/css"/>
	   <link rel="icon" href="image/page2-icon.jpg"> 
	   <img src="image/hot_cold.jpg" alt="led_on_image" id="image_hot_cold">
	
	   <script type="text/javascript" >
	     
	   </script>
    </head>

    <body>
	 <h1>Home Automation Project</h1>
	 <div id="info">SAMEER ASIRI <br/>Email: semmoor@gmail.com</div>
	 
     <!-- put the image of the device when the system starts depending on the value read from server-->
		<?php 
            //get data from database the to select image of devices besed on data read from database
		    $result = mysqli_query($con,"SELECT * FROM table1"); 
		    /*loop through data read from database to select image of devices besed on data read from database*/  
			while($row = mysqli_fetch_array($result)) 
			{
				/*store value of LED from database into $current_LED, and put image 
				 of the LED in the page depending on value read from database*/
			     $current_LED = $row['LED']; 
				 if($current_LED == 0) 
				 {
					echo"   <img id='image_led' onclick='change_image_led()' src='image/led_off.jpg' > ";
				 }
				 else
				 {
					echo"   <img id='image_led' onclick='change_image_led()' src='image/led_on.jpg' > ";
				 }
				 				 
				 /*store value of fan from database into $current_FAN and put image 
				of the FAN in the page depending on value read from database*/
			    $current_FAN = $row['FAN']; 
				 if($current_FAN == 0) 
				 {
					echo"<img id='image_fan' onclick='change_image_fan()' src='image/fan_off.jpg'>";
				 }
				 else
				 {
					echo"<img id='image_fan' onclick='change_image_fan()' src='image/fan_on.jpg'>";
				 }
				 
				  /*store value of heater from database into $current_HEATER and put image 
				 of the HEATER in the page depending on value read from database*/
			     $current_HEATER = $row['HEATER']; 
				 if($current_HEATER == 0) 
				 {
				 echo"<img id='image_heater' onclick='change_image_heater()' src='image/heater_off.jpg'>";
				 }
				 else
				 {
				echo"<img id='image_heater' onclick='change_image_heater()' src='image/heater_on.jpg'>";
				 } 
			}
			?> 	 
	 
	 <?php
		
		/*
		  columns id,LIGHT BULB	,TEMPERATURE these are the header of the table
		*/
		echo 
		"
		<table border='4' id='table'>
		<tr>
		<th>id</th>
		<th>LIGHT BULB</th>
		<th>FAN</th>
		<th>HEATER</th>
		<th>TEMPERATURE</th>
		</tr>
		";
		
		//get data from database the to put in the table all
		$result = mysqli_query($con,"SELECT * FROM table1"); 
		//loop through data read from database to put in the table
		while($row = mysqli_fetch_array($result)) 
		{
			echo "<tr>"; //drawing second row

			//store id value from database into $unit_id & put it in first cell in web page
			$unit_id = $row['id']; 
			echo "<td>" . $row['id'] . "</td>"; 
			
			//store value of LED from database into $current_LED
			$column_LED = "LED";  
			$current_LED = $row['LED']; 
					
			
			//store value of HEATER from database into $current_HEATER
			$column_HEATER = "HEATER";  
			$current_HEATER = $row['HEATER']; 
			
				
			//store value of FAN from database into $current_FAN
			$column_FAN = "FAN";  
			$current_FAN = $row['FAN']; 
				
								
			/*
			   for the LIGHT BULB cell
			   create submit button in the cell.
			   create text box in the cell and display current LIGHT BULB value inside it.
			   create a hidden text box and store the value of unit inside it.
			   create a hidden text box and store the value of column inside it.
			   
			   when submit button is pressed send the value of LIGHT BULB ,unit,column of the LIGHT BULB to the database base to be stored in the right unit number and column.	   
			*/
			echo 
			"
			<td>
			<form id='led_form' action= database.php method='post'>
			<input id='led_text_box' type='text' name='value' value=$current_LED size='10' maxlength='1'> 
			<input type='hidden' name='unit' value=$unit_id >
			<input type='hidden' name='column' value=$column_LED >
			<input id='submit_button' type= 'submit' name= 'change_but' style='text-align:center' value='LIGHT ON/OFF'>
			</form>
			</td>
			";
			
			/*
			   for the FAN cell
			   create submit button in the cell.
			   create text box in the cell and display current FAN value inside it.
			   create a hidden text box and store the value of unit inside it.
			   create a hidden text box and store the value of column inside it.
			   
			   when submit button is pressed send the value of FAN ,unit,column of the FAN to the database base to be stored in the right unit number and column.	   
			*/
			echo 
			"
			<td>
			<form  id='fan_form' action= database.php method='post'>
			<input id='fan_text_box' type='text' name='value' value=$current_FAN size='10' maxlength='1'> 
			<input type='hidden' name='unit' value=$unit_id >
			<input type='hidden' name='column' value=$column_FAN >
			<input id='submit_button' type= 'submit' name= 'change_but' style='text-align:center' value='FAN ON/OFF'>
			</form>
			</td>
			";
			
			/*
			   for the HEATER cell
			   create submit button in the cell.
			   create text box in the cell and display current HEATER value inside it.
			   create a hidden text box and store the value of unit inside it.
			   create a hidden text box and store the value of column inside it.
			   
			   when submit button is pressed send the value of HEATER ,unit,column of the HEATER to the database base to be stored in the right unit number and column.	   
			*/
			echo 
			"
			<td>
			<form id='heater_form' action= database.php method='post'>
			<input id='heater_text_box' type='text' name='value' value=$current_HEATER size='10' maxlength='1'> 
			<input type='hidden' name='unit' value=$unit_id >
			<input type='hidden' name='column' value=$column_HEATER >
			<input id='submit_button' type= 'submit' name= 'change_but' style='text-align:center' value='HEATER ON/OFF'>
			</form>
			</td>
			";
					
			//put the value of the TEMP in the  cell in web page
			echo "<td>" . $row['TEMP'] . "</td>";
				
		}
		echo "</tr>";  //end of second row
		echo "</table>";  //end of table
?>


<script>

	/*this function is called when the image of led is pressed to change the 
    image & change the value of the led then submit the form of the led to database*/
	function change_image_led() {
	var image = document.getElementById('image_led');
	if (image.src.match("image/led_on.jpg")) 
	{
		image.src = "image/led_off.jpg";
		document.getElementById("led_text_box").value = 0;
	} 
	else 
	{
		image.src = "image/led_on.jpg";
		document.getElementById("led_text_box").value = 1;
	}
	document.getElementById("led_form").submit();
    }
		  
    /*this function is called when the image of fan is pressed to change the 
     image & change the value of the fan then submit the form of the fan to database*/
	function change_image_fan() {
	var image = document.getElementById('image_fan');
	if (image.src.match("image/fan_on.jpg")) {
		image.src = "image/fan_off.jpg";
		document.getElementById("fan_text_box").value = 0;
	} else {
		image.src = "image/fan_on.jpg";
		document.getElementById("fan_text_box").value = 1;
	}
	document.getElementById("fan_form").submit();
    }
		  
    /*this function is called when the image of heater is pressed to change the 
     image & change the value of the heater then submit the form of the heater to database*/
	function change_image_heater() {
	var image = document.getElementById('image_heater');
	if (image.src.match("image/heater_on.jpg")) {
		image.src = "image/heater_off.jpg";
		document.getElementById("heater_text_box").value = 0;
	} else {
		image.src = "image/heater_on.jpg";
		document.getElementById("heater_text_box").value = 1;
	}
	document.getElementById("heater_form").submit();
    }
</script>
</body>
</html>
