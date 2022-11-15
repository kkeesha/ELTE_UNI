<?php
include('storage.php');
include('auth.php');
include('userStorage.php');

function redirect($page)
{
    header("Location: ${page}");
    exit();
}



$user_Storage = new UserStorage();
$auth = new Auth($user_Storage);
$data = [];
$errors = [];
function validate($post, &$data, &$errors)
{
    $data = $post;
    $username = $post['username'];
    if (!isset($username)) $errors['username'] = "Username is required";
    else if (trim($username) === '') $errors['username'] = "Username is empty";
    else $data['username'] = $username;

    $email = $post['email'];
    if (trim($email) === '') $errors['email'] = "Email address is required";
    else if (!filter_var($email, FILTER_VALIDATE_EMAIL) !== false) $errors['email'] = "Not valid email format";

    $password = $post['password'];
    if (trim($password) === '') $errors['password'] = "Password is not set";

    $confirm = $post['confirm'];
    if ($confirm === '' &&  $password !== '') $errors['confirm'] = "Confirm your password";
    else if ($confirm != $password && $password !== '') $errors['confirm'] = "Password is not matching";

    return count($errors) === 0;
}

if (count($_POST) > 0) {
    if (validate($_POST, $data, $errors)) {
        if ($auth->user_exists($data['email'])) {
            $errors['email'] = "User already exists!";
        } else if ($auth->user_exists($data['email'])) {
            $errors['email'] = "User already exists!";
        } else {
            $auth->register($data);
            redirect('login.php');
        }
    }
}
?>


<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ELTE Arena Stadium</title>
    <style>
        input+span {
            font-size: 15px;
            color: red;
        }
    </style>
</head>

<body>
    <h2>Please, fill out the form to be registered in our system</h2>
    <form action="" method="post" style="font-size: 17px;" novalidate>
        Your username: <br>
        <input type="text" name="username" required value="<?= $_POST['username'] ?? '' ?>">
        <?php if (isset($errors['username'])) : ?>
            <span><?= $errors['username'] ?></span>
        <?php endif ?>
        <br>
        Your email address:<br>
        <input type="email" name="email" required value="<?= $_POST['email'] ?? '' ?>">
        <?php if (isset($errors['email'])) : ?>
            <span><?= $errors['email'] ?></span>
        <?php endif ?>
        <br>
        Create password:<br>
        <input type="password" name="password" required value="<?= $_POST['password'] ?? '' ?>">
        <?php if (isset($errors['password'])) : ?>
            <span><?= $errors['password'] ?></span>
        <?php endif ?>
        <br>
        Confirm the password:<br>
        <input type="password" name="confirm" class="confirm" required value="<?= $_POST['confirm'] ?? '' ?>">
        <?php if (isset($errors['confirm'])) : ?>
            <span><?= $errors['confirm'] ?></span>
        <?php endif ?>
        <br><br>
        <button style="font-size: 15px;">Register</button>
    </form>
    <h4><a href="index.php">Main Page</a></h4>
    <h4>Already have an account? Log in <a href="login.php">here</a></h4>
</body>

</html>