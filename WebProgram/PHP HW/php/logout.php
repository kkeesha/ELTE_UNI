<?php
include('storage.php');
include('auth.php');
include('userStorage.php');

session_start();
$user_storage = new userStorage();
$auth = new Auth($user_storage);

function redirect($page)
{
    header("Location: ${page}");
    exit();
}

$auth->logout();
redirect('login.php');
