<?php

// server
$servername = "localhost";
// db_name
$dbname = "db_name";
// username
$username = "username";
// password
$password = "password";

// change this value and change in your .ino sketch
$api_key_value = "y0urAPI6x4!";

$api_key= $Home = $Voltage = $Current = $Power = $Energy = $Frequency = $PF = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = test_input($_POST["api_key"]);
    if($api_key == $api_key_value) {
        $Home = test_input($_POST["Home"]);
        $Voltage = test_input($_POST["Voltage"]);
        $Current = test_input($_POST["Current"]);
        $Power = test_input($_POST["Power"]);
        $Energy = test_input($_POST["Energy"]);
        $Frequency = test_input($_POST["Frequency"]);
        $PF = test_input($_POST["PF"]);
        
        // Create connection
        $conn = new mysqli($servername, $username, $password, $dbname);
        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
        
        $sql = "INSERT INTO TableName (Home, Voltage, Current, Power, Energy, Frequency, PF)
        VALUES ('" . $Home . "', '" . $Voltage . "', '" . $Current . "', '" . $Power . "', '" . $Energy . "', '" . $Frequency . "', '" . $PF . "')";
        
        if ($conn->query($sql) === TRUE) {
            echo "New record created successfully";
        } 
        else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
    
        $conn->close();
    }
    else {
        echo "Wrong API Key provided.";
    }

}
else {
    echo "No data posted with HTTP POST.";
}

function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}