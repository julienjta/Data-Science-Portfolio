<?php
  session_start();
?>
<?php 
    include 'traduction.php';
?>

<?php
if (!$_SESSION["connected_user"]) {
header('Location: login.php');
}
?> 

<!doctype html>
<html lang="fr">
<head>
  <meta charset="utf-8">
  <title>Mon Compte</title>
  <link rel="stylesheet" type="text/css" media="all"  href="css/mystyle.css" />
</head>
<body>
    <header>
        <form method="POST" action="controller.php">
            <input type="hidden" name="action" value="disconnect">
            <input type="hidden" name="loginPage" value="login.php?disconnect">
            <button class="btn-logout form-btn">Déconnexion</button>
        </form>
        
        <h2><?php echo $_SESSION["connected_user"]["prenom"];?> <?php echo $_SESSION["connected_user"]["nom"];?> - Mon compte</h2>
    </header>

    <!--HAUT DE LA PAGE-->
    <?php 
            include 'header.php';
        ?>



        <!--PIED DE LA PAGE-->
        <?php 
            include 'footer.php';
        ?>

</body>
</html>