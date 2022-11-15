<?php
include('storage.php');
include('auth.php');
include('userStorage.php');

class commentStorage extends Storage
{
    public function __construct()
    {
        parent::__construct(new JsonIO('comments.json'));
    }
}

$teamsStorage = new Storage(new JsonIO('teams.json'));
$matchesStorage = new Storage(new JsonIO('matches.json'));
$commentsStorage = new Storage(new JsonIO('comments.json'));

$id = $_GET['id'];
$team = $teamsStorage->findById($id);
$teams = $teamsStorage->findAll();
$match = $matchesStorage->findAll();
$comments = $commentsStorage->findAll();

// function disable(){
//     echo "disabled";
// }
// function alert(){
//     echo "<span>" ."Login to your account to enable commenting!"."</span>";
// }


function redirect($page)
{
    header("Location: ${page}");
    exit();
}

session_start();
$user_storage = new userStorage();
$auth = new Auth($user_storage);
$data = [];
$errors = [];


function validate($post, &$data, &$errors)
{
    $data = $post;
    $comment = $post['comment'];
    if (!isset($comment)) $errors['comment'] = "Comment is required";
    else if (trim($comment) === '') $errors['comment'] = "Comment is empty";
    else $data['comment'] = $comment;

    return count($errors) === 0;
}

if (count($_POST) > 0) {
    if (validate($_POST, $data, $errors)) {
        $commentsStorage = new commentStorage();
        $commentsStorage->add([
            'team' => $team['name'],
            'username' => $_POST['username'],
            'comment' => $_POST['comment'],
            'date' => $_POST['date']
        ]);
        redirect('teamDetails.php?id=' . $id);
    }
}

// echo "<br>" . 312312;
// foreach($comments as $com){
//     echo "<br>";
//     echo $com['comment'];
// }



$lose = "lightcoral";
$win = "lightgreen";
$draw = "#FFFF99";
$color;
$yourScore;
$opponentScore;

?>


<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <?php if (isset($_SESSION['user'])) : ?>
        <p style="">You are logged in as <?php echo $auth->authenticated_user()['username'] ?> || <a href="logout.php">Logout</a></p>
    <?php endif ?>
    <title>ELTE Arena Stadium</title>
    <style>
        span {
            font-size: 15px;
            color: red;
        }
    </style>
</head>

<body>
    <h1><?= $team['name'] ?></h1>

    <?php if (!isset($_SESSION['user'])) { ?>
        <table>
            <tr>
                <th>Home</th>
                <th>VS</th>
                <th>Away</th>
            </tr>
            <?php

            foreach ($match as $elem) :
                $homeTeam = $elem['home']['teamid'];
                $awayTeam = $elem['away']['teamid'];
            ?>
                <?php if ($elem['home']['teamid'] == $team['teamid'] || $elem['away']['teamid'] == $team['teamid']) : ?>
                    <tr>
                        <td><?= $team['name'] ?></td>
                        <td>vs</td>
                        <td>

                            <?php if ($homeTeam == $team['teamid']) {

                                $opponentId =  $awayTeam;
                                if ($opponentId == 1) echo "Bayern Munich";
                                else if ($opponentId == 2) echo  "Ferencvaros";
                                else echo "Atletico de Madrid";
                            } else if ($awayTeam == $team['teamid']) {
                                $opponentId =  $homeTeam;
                                if ($opponentId == 1) echo "Bayern Munich";
                                else if ($opponentId == 2) echo  "Ferencvaros";
                                else echo "Atletico de Madrid";
                            }
                            ?>
                        </td>
                    </tr>

                <?php endif ?>
            <?php endforeach ?>

        </table>

    <?php } else { ?>
        <table>
            <tr>
                <th style="font-weight: 900;">Your Team</th>
                <th>Score</th>
                <th>Opponent Team</th>
                <th>Home - Away</th>
            </tr>

            <!-- team`s score, away-home based on the team you select -->

            <?php
            foreach ($match as $elem) : ?>
                <?php if ($elem['home']['teamid'] == $team['teamid'] || $elem['away']['teamid'] == $team['teamid']) : ?>
                    <?php
                    $homeScore = $elem['home']['score'];
                    $awayScore = $elem['away']['score'];
                    $homeTeam = $elem['home']['teamid'];
                    $awayTeam = $elem['away']['teamid'];
                    ?>
                    <tr>
                        <td style="background-color:
                    <?php if ($homeTeam == $team['teamid'])
                        $yourScore = $homeScore;
                    else $yourScore = $awayScore;
                    if ($homeTeam == $team['teamid']) $opponentScore = $awayScore;
                    else $opponentScore = $homeScore;
                    if ($yourScore > $opponentScore) $color = $win;
                    else if ($yourScore < $opponentScore) $color = $lose;
                    else $color = $draw;
                    echo $color;
                    ?>;
                        font-weight: bold;
                    "><?= $team['name'] ?></td>
                        <td>
                            <?php if ($homeTeam == $team['teamid']) {
                                echo $homeScore;
                                $yourScore = $homeScore;
                            } else {
                                echo $awayScore;
                                $yourScore = $awayScore;
                            }
                            ?>
                            :
                            <?php if ($homeTeam == $team['teamid']) {
                                echo $awayScore;
                                $opponentScore = $awayScore;
                            } else {
                                echo $homeScore;
                                $opponentScore = $homeScore;
                            }
                            ?>
                        </td>
                        <td style="background-color: 
                    <?php if ($homeTeam == $team['teamid'])
                        $yourScore = $homeScore;
                    else $yourScore = $awayScore;
                    if ($homeTeam == $team['teamid']) $opponentScore = $awayScore;
                    else $opponentScore = $homeScore;
                    if ($yourScore < $opponentScore) $color = $win;
                    else if ($yourScore > $opponentScore) $color = $lose;
                    else $color = $draw;
                    echo $color;
                    ?>;
                    ">

                            <?php if ($homeTeam == $team['teamid']) {
                                $opponentId =  $awayTeam;
                                if ($opponentId == 1) echo "Bayern Munich";
                                else if ($opponentId == 2) echo  "Ferencvaros";
                                else echo "Atletico de Madrid";
                            } else if ($awayTeam == $team['teamid']) {
                                $opponentId =  $homeTeam;
                                if ($opponentId == 1) echo "Bayern Munich";
                                else if ($opponentId == 2) echo  "Ferencvaros";
                                else echo "Atletico de Madrid";
                            }
                            ?>
                        </td>
                        <td>
                            <?php if ($homeTeam == $team['teamid']) echo "Home";
                            else echo "Away";
                            ?>
                        </td>
                    </tr>

                <?php endif ?>
            <?php endforeach ?>

        </table>
    <?php } ?>

    <h4><a href="index.php">Main Page</a></h4>

    <form action="" method="post" style="font-size: 17px;" novalidate>
        Comment for <?= $team['name'] ?>: <br>
        <input type="text" name="username" style="display: none;" value="<?php echo $auth->authenticated_user()['username'] ?>">
        <textarea class="textarea" name="comment" value="<?= $_POST['comment'] ?? '' ?>"></textarea>
        <?php if (isset($errors['comment'])) : ?>
            <span><?= $errors['comment'] ?></span>
        <?php endif ?>
        <input type="text" name="date" style="display: none;" value="<?php echo date('m/d/Y') . " , " . date('H:i') ?>">
        <br>
        <?php
        $disabled = "";
        if (!$auth->is_authenticated()) {
            $disabled = "disabled";
            $warn = "Log in to your account for commenting!";
        } else $warn = "";
        ?>
        <button class="button" id="button" <?= $disabled ?>>Submit</button> <span><?= $warn ?></span>
    </form>


    <h2>Commentaries</h2>
    <?php foreach ($comments as $elem) : ?>
        <div class="comment">
            <?php if ($elem['team'] == $team['name']) : ?>
                <h5><?= $elem['username'] ?></h5>
                <h5><?= $elem['comment'] ?></h5>
                <h5><?= $elem['date'] ?></h5>
            <?php endif ?>
        </div>
    <?php endforeach ?>



    <!-- some styling of the table -->
    <style>
        img {
            width: 28px;
            height: 28px;
        }

        .comment {
            border-radius: 1px;
            background-color: #66ff99;
            margin-right: 900px;
        }

        .button {
            padding: 5px 10px;
            box-shadow: 0px 0px 12px -2px rgba(0, 0, 0, 0.5);
            line-height: 1.25;
            background: #FC6E51;
            text-decoration: none;
            color: white;
            font-size: 10px;
            letter-spacing: .08em;
            text-transform: uppercase;
            position: relative;
            transition: background-color .6s ease;
            overflow: hidden;

            &:after {
                content: "";
                position: absolute;
                width: 0;
                height: 0;
                top: 50%;
                left: 50%;
                top: var(--mouse-y);
                left: var(--mouse-x);
                transform-style: flat;
                transform: translate3d(-50%, -50%, 0);
                background: rgba(white, .1);
                border-radius: 100%;
                transition: width .3s ease, height .3s ease;
            }

            &:focus,
            &:hover {
                background: darken(#FC6E51, 7%);
            }

            &:active {
                &:after {
                    width: 300px;
                    height: 300px;
                }
            }
        }

        textarea {
            border-radius: 10px;
        }

        span {
            font-size: 15px;
        }

        table {
            width: 400px;
            height: 200px;
        }

        table,
        th,
        td {
            border: 2px solid black;
            border-collapse: collapse;
        }

        th,
        tr {
            text-align: center;
        }

        .textarea {
            resize: none;
            height: 70px;
            width: 200px;
        }
    </style>
</body>

</html>