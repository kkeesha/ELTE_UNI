<?php
include('storage.php');
include('auth.php');
include('userStorage.php');

// functions
function redirect($page)
{
    header("Location: ${page}");
    exit();
}


function validate($post, &$data, &$errors)
{
    $data = $post;
    $username = $post['username'];
    if (!isset($username)) $errors['username'] = "Username is required";
    else if (trim($username) === '') $errors['username'] = "Username is empty";
    else $data['username'] = $username;

    $password = $post['password'];
    if (trim($password) === '') $errors['password'] = "Password is not set";

    return count($errors) === 0;
}

// main
session_start();
$user_storage = new UserStorage();
$auth = new Auth($user_storage);
$data = [];
$errors = [];
if (count($_POST) > 0) {
    if (validate($_POST, $data, $errors)) {
        $auth_user = $auth->authenticate($data['username'], $data['password']);
        if (!$auth_user) {
            $errors['global'] = "Login error";
        } else {
            $auth->login($auth_user);
            redirect('index.php');
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

        form {
            font-size: 17px;
        }
    </style>
</head>

<body>
    <h2>Please, log in to your existing account</h2>
    <?php if (isset($errors['global'])) : ?>
        <p><span class="error"><?= $errors['global'] ?></span></p>
    <?php endif; ?>
    <form action="" method="post">
        <div>
            <label for="username">Username: </label><br>
            <input type="text" name="username" id="username" value="<?= $_POST['username'] ?? "" ?>">
            <?php if (isset($errors['username'])) : ?>
                <span class="error"><?= $errors['username'] ?></span>
            <?php endif; ?>
        </div>
        <div>
            <label for="password">Password: </label><br>
            <input type="password" name="password" id="password">
            <?php if (isset($errors['password'])) : ?>
                <span class="error"><?= $errors['password'] ?></span>
            <?php endif; ?>
        </div>
        <div>
            <br>
            <button type="submit">Login</button>
        </div>
    </form>
    <h4><a href="index.php">Main Page</a></h4>
    <h4>Don`t have an account?<br>Register in our system <a href="register.php">here</a></h4>
</body>

</html>