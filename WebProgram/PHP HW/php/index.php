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

$teamsStorage = new Storage(new JsonIO('teams.json'));
$matchesStorage = new Storage(new JsonIO('matches.json'));

$teams = $teamsStorage->findAll();
$matches = $matchesStorage->findAll();
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ELTE Arena Stadium</title>
</head>

<body>
    <div class="stadium">
        <h1>ELTE Arena Stadium</h1>
    </div>
    <div class="instruc">
        <h3>Click on your a team you want to know about further details</h3>
    </div>
    <?php if (isset($_SESSION['user'])) : ?>
        <p style="">You are logged in as <?php echo $auth->authenticated_user()['username'] ?> || <a href="logout.php">Logout</a></p>
    <?php endif ?>
    <ul>
        <?php foreach ($teams as $teamName) : ?>
            <li style="font-size: 20px;"><a href="teamDetails.php?id=<?= $teamName['id'] ?>"><?= $teamName['name'] ?></a></li>
        <?php endforeach ?>
    </ul>

    <?php if (isset($_SESSION['user'])) : ?>
        <table>
            <tr>
                <th>Home</th>
                <th>VS</th>
                <th>Away</th>
            </tr>
            <?php foreach ($matches as $elem) : ?>
                <?php
                $homeTeam = $elem['home']['teamid'];
                $awayTeam = $elem['away']['teamid'];
                ?>
                <tr>
                    <td>
                        <?php if ($homeTeam == 1) echo "Bayern Munich";
                        else if ($homeTeam == 2) echo  "Ferencvaros";
                        else echo "Atletico de Madrid";
                        ?>
                    </td>
                    <td>vs</td>
                    <td>
                        <?php if ($awayTeam == 1) echo "Bayern Munich";
                        else if ($awayTeam == 2) echo  "Ferencvaros";
                        else echo "Atletico de Madrid";
                        ?>
                    </td>
                </tr>
            <?php endforeach ?>
        </table>
    <?php endif ?>

    <p class="links">
        <a href="login.php">Login</a>
        <br>
        <br>
        <a href="register.php">Register</a>
    </p>



    <style>
        li {
            color: #ff0000;
        }

        body {
            background-color: #fafafa;
        }

        .stadium {
            margin-top: 0;
            width: 100%;
            height: 50px;
            color: #263849;
        }

        .instruc {
            color: #260c1a;
        }

        tr:first-child {
            background-color: #f95959 !important;
        }

        tr:nth-child(even) {
            background-color: #ff9a3c;
        }

        tr:nth-child(odd) {
            background-color: #e0ebeb;
        }


        .links {
            font-size: 15px;
        }

        table {
            width: 350px;
            height: 250px;
        }

        th {
            text-align: left;
        }

        table,
        th,
        td {
            font-size: 17px;
            border: 3px solid black;
            border-collapse: collapse;
        }

        th,
        tr {
            text-align: center;
        }
    </style>
</body>

</html>