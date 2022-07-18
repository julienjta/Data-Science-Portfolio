<?php
  require_once('modele.php');
  
  session_start();
  
  // URL de redirection par défaut (si pas d'action ou action non reconnue)
  $url_redirect = "index.php";
  
  if (isset($_REQUEST['action'])) {
  
      if ($_REQUEST['action'] == 'authenticate') {
          /* ======== AUTHENT ======== */
          if (!isset($_REQUEST['login']) || !isset($_REQUEST['mdp']) || $_REQUEST['login'] == "" || $_REQUEST['mdp'] == "") {
              // manque login ou mot de passe
              $url_redirect = "login.php?nullvalue";
              
          } else {
          
              $utilisateur = connexionParLoginPwd($_REQUEST['login'], $_REQUEST['mdp']);
              
              if ($utilisateur == false) {
                // echec authentification
                $url_redirect = "login.php?badvalue";
                
              } else {
                // authentification réussie
                $_SESSION["connected_user"] = $utilisateur;
                $_SESSION["nom"] = "test";//$_REQUEST['login'];
                //$_SESSION["listeUsers"] = findAllUsers();
                $url_redirect = "admin.php";
              }
          }
        } else if ($_REQUEST['action'] == 'disconnect') {
            /* ======== DISCONNECT ======== */
            unset($_SESSION["connected_user"]);
            $url_redirect = "index.php" ;
            
        }
    }
    header("Location: $url_redirect");
?>