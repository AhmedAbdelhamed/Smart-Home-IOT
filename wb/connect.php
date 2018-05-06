<?php
   //connect to the database
	$con = mysqli_connect("localhost", "root", "1234", "IOT"); 
		
	// Check connection, if error display error message
	if (mysqli_connect_errno())
	{
	  die('Failed to connect to MySQL: ' . mysqli_connect_error());
	}
?>
