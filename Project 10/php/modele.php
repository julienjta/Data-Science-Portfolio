   <?php

function getMySqliConnection() {

  $mysqli = new mysqli($db_connection_array['DB_HOST'], $db_connection_array['DB_USER'], $db_connection_array['DB_PASSWD'], $db_connection_array['DB_NAME']);
  //$mysqli = new mysqli("127.0.0.1:3308", "root", "", "tx");

  if(is_null($mysqli->connect_error)){
   //echo "Holo is a Wise connected Wolf";
  }else {
   echo "Failed to access to DB - Error " .$mysqli->connect_errno;
   exit();
   }
  
  return $mysqli;
}

function getAdminLogin()
 {
    $admin_login = parse_ini_file("/volgen/user1x/users/wrbvshoecustom/config/config.ini");
    return $admin_login['ADMIN_USER'];
 }

 function getAdminPSW()
 {
    $admin_psw = parse_ini_file("/volgen/user1x/users/wrbvshoecustom/config/config.ini");
    return $admin_psw['ADMIN_PASSWD'];
 }


// Fonction d'authentification
 function connexionParLoginPwd($login, $pwd) 
 {
    $admin_login = getAdminLogin();
    $admin_psw = getAdminPSW();

    if ($admin_login == '' || $admin_psw == '') 
    {
		echo 'Erreur lecture fichier de conf';
		$utilisateur = false;
    } 
    else 
    {	
        if ($admin_login == $login && $admin_psw == hash(md5, $pwd)) // si stored hash pswd = hash(input pswd) => OK
        {
			$utilisateur = true;
        }
        else 
        {
			$utilisateur = false;
		}
	}
  
	return $utilisateur;
}

// Fonction pour envoyer les données du quiz vers la base de données
function sendQuizDataToDatabase($id_customer, $jogger, $trail, $hiker, $walker, $stride_type, $foot_width, $outdoor, $indoor, $nature, $summer, $rainy, $winter, $Moisture_wicking, $water_resistant, $waterproof, $Breathable, $Anckle_support, $shoe_weight, $shoe_comfort)
{
   $mysqli = getMySqliConnection();

   if ($mysqli->connect_error) {
      echo 'Erreur connection BDD (' . $mysqli->connect_errno . ') '. $mysqli->connect_error;
   } else {
      $sql = "INSERT INTO `DATA` (`id_custommer`, `jogger`, `trail`, `hiker`, `walker`, `stride_type`, `foot_width`, `outdoor`, `indoor`, `nature`, `summer`, `rainy`, `winter`, `Moisture_wicking`, `water_resistant`, `waterproof`, `Breathable`, `Anckle_support`, `shoe_weight`, `shoe_comfort`) VALUES ('$id_customer', '$jogger', '$trail', '$hiker', '$walker', '$stride_type', '$foot_width', '$outdoor', '$indoor', '$nature', '$summer', '$rainy', '$winter', '$Moisture_wicking', '$water_resistant', '$waterproof', '$Breathable', '$Anckle_support', '$shoe_weight', '$shoe_comfort')";
      if (mysqli_query($mysqli, $sql)) {
         echo "New record created successfully";
      } else {
         echo "Error: " . $sql . "<br>" . mysqli_error($mysqli);
      }
   mysqli_close($mysqli);
   }
}

// Fonction pour envoyer les données du questionnaire vers la base de données
function sendSurveyDataToDatabase($id_customer, $gender, $age, $like_shoe, $meet_needs, $ideal_shoe, $website, $recommendation, $change_product, $change_experience)
{
   $mysqli = getMySqliConnection();

   if ($mysqli->connect_error) {
      echo 'Erreur connection BDD (' . $mysqli->connect_errno . ') '. $mysqli->connect_error;
   } else {
      $sql = "UPDATE `DATA` SET `gender`=$gender, `age`=$age, `like_shoe`=$like_shoe, `meet_needs`=$meet_needs, `ideal_shoe`=$ideal_shoe, `website`=$website, `recommendation`=$recommendation, `change_product`=$change_product, `change_experience`=$change_experience) WHERE `id_customer`=$id_customer";
      if (mysqli_query($mysqli, $sql)) {
         echo "New record created successfully";
      } else {
         echo "Error: " . $sql . "<br>" . mysqli_error($mysqli);
      }
   mysqli_close($mysqli);
   }
}

// Fonction pour demander à la BDD les réponses du quiz, données stockées dans un tableau
function getQuizData() {
   $mysqli = getMySqliConnection();
 
   $listeQuizData = array();
 
   if ($mysqli->connect_error) {
       echo 'Erreur connection BDD (' . $mysqli->connect_errno . ') '. $mysqli->connect_error;
   } else {
       $req="SELECT `id_customer`,`jogger`,`hiker`,`trail`,`walker`,`stride_type`,`foot_width`,`outdoor`,`indoor`,`nature`,`summer`,`rainy`,`winter`,`Moisture_wicking`,`water_resistant`,`waterproof`,`Breathable`,`Anckle_support`,`shoe_weight`,`shoe_comfort` FROM `DATA` WHERE 1 ";
       if (!$result = $mysqli->query($req)) {
           echo 'Erreur requête BDD ['.$req.'] (' . $mysqli->errno . ') '. $mysqli->error;
       } else {
           while ($unData = $result->fetch_assoc()) {
             $listeQuizData[$unData['id_customer']] = $unData;
           }
           $result->free();
       }
       $mysqli->close();
   }
 
   return $listeQuizData;
 }

 // Fonction pour demander à la BDD les réponses du questionnaire, données stockées dans un tableau
 function getSurveyData() {
   $mysqli = getMySqliConnection();
 
   $listeSurveyData = array();
 
   if ($mysqli->connect_error) {
       echo 'Erreur connection BDD (' . $mysqli->connect_errno . ') '. $mysqli->connect_error;
   } else {
       $req="SELECT `id_customer`, `gender`,`age`,`like_shoe`,`meet_needs`,`ideal_shoe`,`website`,`recommendation`,`change_product`,`change_experience` FROM `DATA` WHERE 1 ";
       if (!$result = $mysqli->query($req)) {
           echo 'Erreur requête BDD ['.$req.'] (' . $mysqli->errno . ') '. $mysqli->error;
       } else {
           while ($unData = $result->fetch_assoc()) {
             $listeSurveyData[$unData['id_customer']] = $unData;
           }
           $result->free();
       }
       $mysqli->close();
   }
 
   return $listeSurveyData;
 }


 


?>