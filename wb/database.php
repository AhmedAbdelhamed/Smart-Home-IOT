<?php include 'connect.php' ; ?>
<?php

		//get the post variables from homepage
		$value = $_POST['value'];
		$unit = $_POST['unit'];
		$column = $_POST['column'];
		
		//update the value of posted column from page in database
		mysqli_query($con,"UPDATE table1 SET $column = '{$value}'
		WHERE id=$unit");

		//go back to the homepage index.php
		header("location: page.php");
?>
