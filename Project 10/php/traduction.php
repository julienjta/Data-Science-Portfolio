<!--DOCUMENT PERMETTANT DE GERER LE SYSTEME MULTILINGUE-->

<?php
    $langue = "eng"; // La langue par défaut
       if(isset($_COOKIE['langue'])) // Si la langue a déjà été enregistrée sur l'odinateur du client
       {
           $langue = $_COOKIE['langue'];
       }
       else  // Si aucune langue n'est déclarée on tente de reconnaitre la langue par défaut du navigateur
       {
           $langue = substr($_SERVER['HTTP_ACCEPT_LANGUAGE'],0,2);
       }

       if(isset($_POST['langue'])) // Si un nouveau choix de langue a été fait, on change la langue
       {
               $langue=$_POST['langue'];
       }
    
    
       $expire = 365*24*3600;  // Définition de la durée du cookie (1 an)
       setcookie('langue', $langue, time() + $expire);

       $json = file_get_contents("traduction5.json"); // On récupère les traductions contenues dans le fichier .json et on le "parse"
       $parsed_json = json_decode($json);
?>

