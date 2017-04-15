<?php
header('Access-Control-Allow-Origin: *');
$db_host = 'localhost'; //hostname
$db_user = 'pandora_read'; // username
$db_password = 'pandora2'; // password
$db_name = 'pandora2'; //database name
$conn = mysql_connect($db_host, $db_user, $db_password );
mysql_select_db($db_name, $conn);
?>
