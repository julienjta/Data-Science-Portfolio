<!doctype html>
<?php
    include 'traduction.php';
?>


<html>
<head>
  <meta charset="utf-8">
  <title>Connexion</title>
  <link rel="stylesheet" type="text/css" media="all"  href="css/mystyle.css" />
</head>
<body>
  <?php
      include 'header.php';
  ?>
  
  <section>
<h1 style="color:black;">Connexion</h1>
      <div class="login-page">
        <div class="form-login">
            <form method="POST" action="controller.php">
                <input type="hidden" name="action" value="authenticate">
                <input type="text" name="login" placeholder="login"/>
                <input type="password" name="mdp" placeholder="mot de passe"/>
                <button>login</button>
            </form>
        </div>
      </div>

      <?php
      if (isset($_REQUEST["nullvalue"])) {
        echo '<p class="errmsg">Merci de saisir votre login et votre mot de passe</p>';
      } else if (isset($_REQUEST["badvalue"])) {
        echo '<p class="errmsg">Votre login/mot de passe est incorrect</p>';
      } else if (isset($_REQUEST["disconnect"])) {
        echo '<p>Vous avez bien été déconnecté.</p>';
      }
      ?>
  </section>
<?php
    include 'footer.php';
?>
</body>
</html>
