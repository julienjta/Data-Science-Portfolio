<?php 
    
    
    session_start();
     include 'selected_functions.php';
     include 'traduction.php';
?>

<?php
    include 'optimal_solution.php';
?>

<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8" />
    <title><?php echo $parsed_json->{$langue}->{'index'}->{'titre'};?></title>
    <link rel="stylesheet" href="css/mystyle.css">

<SCRIPT language="Javascript">
var nouveau = "<?php echo $_SESSION['outsole']; ?>"+"-"+"<?php echo $_SESSION['heel']; ?>"+"-white";
document.getElementById('rectangle').style.background = 'url("../images/models/'+nouveau+'.png") no-repeat';
function changer_couleur(id){
    var nouveau = "<?php echo $_SESSION['outsole']; ?>"+"-"+"<?php echo $_SESSION['heel']; ?>"+"-"+id;
        document.getElementById('rectangle').style.background = 'url("../images/models/'+nouveau+'.png") no-repeat';
    document.getElementById('rectangle').style.backgroundSize = "300px";
   document.getElementById('model').innerHTML = nouveau;
}

function valider_couleur(){
    document.getElementById('rectangle').style.width = "400px";
    document.getElementById('rectangle').style.height = "250px";
    document.getElementById('rectangle').style.backgroundSize = "400px";
    document.getElementById('rectangle').style.marginTop = "40px";
    
    document.getElementById('form_couleur').style.display = "none";
    document.getElementById('valider_couleur').style.display = "none";
    document.getElementById('couleur1').style.display = "none";
    document.getElementById('couleur2').style.display = "inline";
    document.getElementById('tick-couleur').style.display = "inline";
}
</SCRIPT>
<style>
#rectangle
{
background: url(<?php echo "\"../images/models/".$_SESSION['outsole']."-".$_SESSION['heel']."-white.png\"";?>) no-repeat;
    background-size: 300px;
}
</style>
    </head>
    
    <body>

        <!--HAUT DE LA PAGE-->
        <?php 
            include 'header.php';
        ?>

        <!--CORPS DE LA PAGE-->
        <section>
                    <article id="modele">


<div class="titre_questionnaire">
    <p><img src="/images/end.png" width="40px" height="40px"></p>
    <h3><?php echo $parsed_json->{$langue}->{'questionnaire'}->{'titrecust'};?> </h3>
</div>

<h5 id="couleur1"><?php echo $parsed_json->{$langue}->{'questionnaire'}->{'sous-titrecust'};?></h5>
<h5 id="couleur2" style="display:none"><?php echo $parsed_json->{$langue}->{'questionnaire'}->{'sous-titrecust2'};?></h5>

<div class="group-modele">


<div style="margin:auto;margin-left:0;margin-right:0;">
<div id="rectangle"></div>


<form method=post action="#"  id="form_couleur">
<div class="noir"><input type="radio" name="couleur" id="noir"  onclick="changer_couleur('black')"><label for="noir"></label></div>
<div class="blanc"><input type="radio" name="couleur" id="blanc"  onclick="changer_couleur('white')" checked><label for="blanc"></label></div>
<div class="jaune"><input type="radio" name="couleur" id="jaune"  onclick="changer_couleur('yellow')"><label for="jaune"></label></div>
<div class="orange"><input type="radio" name="couleur" id="orange"  onclick="changer_couleur('orange')"><label for="orange"></label></div>
<div class="rouge"><input type="radio" name="couleur" id="rouge"  onclick="changer_couleur('red')"><label for="rouge"></label></div>
<div class="bleu"><input type="radio" name="couleur" id="bleu"  onclick="changer_couleur('blue')"><label for="bleu"></label></div>
<div class="vert"><input type="radio" name="couleur" id="vert" onclick="changer_couleur('green')"><label for="vert"></label></div>
</form>
</div>
<div style="margin:auto;margin-left:0;margin-right:0;"><p><button id="valider_couleur" onclick="valider_couleur()" type="submit" value="Submit"><?php echo $parsed_json->{$langue}->{'questionnaire'}->{'boutoncust'};?> >></button></p>
</div>
<p id="tick-couleur" style="display:none;margin:auto;padding:0;margin-left:0;margin-right:0;" ><img src="/images/tick-couleur.png" width="200px" height="200px"></p>
</div>
</article>
</br></br>
</br>

<hr />

                          
                        
                    
                    <br />

                    <article>

                        <!--Question 1/3-->

                        <form method="post" action="fin.php">
                            
                        <div class="titre_questionnaire">
                            <p><img src="/images/tick.png" width="40px" height="40px"></p>
                            <h3><?php echo $parsed_json->{$langue}->{'questionnaire'}->{'titre'};?></h3>
                        </div>
                        <h5><?php echo $parsed_json->{$langue}->{'questionnaire'}->{'descr'};?></h5>
                        <br />

                        <div class="questionnaire">
                            <h4><?php echo $parsed_json->{$langue}->{'questionnaire'}->{'q1'};?></h4>
                            <p class="fleche"><img src="/images/fleche.png" width="20px"></p>
<p><span><?php echo $parsed_json->{$langue}->{'questionnaire'}->{'q1-1'};?>:</span>
                             <input type="radio" name="sex" value="male"/> <?php echo $parsed_json->{$langue}->{'questionnaire'}->{'gender1'};?>
                            <input type="radio" name="sex" value="female"/> <?php echo $parsed_json->{$langue}->{'questionnaire'}->{'gender2'};?>
                            </p>

                            <p><span><?php echo $parsed_json->{$langue}->{'questionnaire'}->{'q1-2'};?> :</span> <input type="text" name="age" size="5" /></p>
                        </div>
                        <br />

                        <div class="questionnaire">
                        <h4><?php echo $parsed_json->{$langue}->{'questionnaire'}->{'q3'};?></h4>

<p class="fleche"><img src="/images/fleche.png" width="20px"></p>
                            <p>
                                <input type="radio" name="q1" id="q1_great" value="great"/> <?php echo $parsed_json->{$langue}->{'questionnaire'}->{'answergreat'};?></br>
                                <input type="radio" name="q1" id="q1_fine" value="fine"/> <?php echo $parsed_json->{$langue}->{'questionnaire'}->{'answerfine'};?></br>
                                <input type="radio" name="q1" id="q1_fineb" value="finebut"/> <?php echo $parsed_json->{$langue}->{'questionnaire'}->{'answerfinebut'};?></br>
                                <input type="radio" name="q1"id="q1_bad" value="bad"/> <?php echo $parsed_json->{$langue}->{'questionnaire'}->{'answerbad'};?>
                            </p> 
                        </div>
                        <br />                      

                        <div class="questionnaire">
                        <h4><?php echo $parsed_json->{$langue}->{'questionnaire'}->{'q4'};?></h4>

<p class="fleche"><img src="/images/fleche.png" width="20px"></p>
                            <p>
                                <input type="radio" name="q3" id="q3_great" value="great"/> <?php echo $parsed_json->{$langue}->{'questionnaire'}->{'answergreat'};?></br>
                                <input type="radio" name="q3" id="q3_fine" value="fine"/> <?php echo $parsed_json->{$langue}->{'questionnaire'}->{'answerfine'};?></br>
                                <input type="radio" name="q3" id="q3_fineb" value="fineb"/> <?php echo $parsed_json->{$langue}->{'questionnaire'}->{'answerfinebut'};?></br>
                                <input type="radio" name="q3"id="q3_bad" value="bad"/> <?php echo $parsed_json->{$langue}->{'questionnaire'}->{'answerbad'};?>
                            </p> 
                        </div>
                        <br />

                        <div class="questionnaire">
                        <h4><?php echo $parsed_json->{$langue}->{'questionnaire'}->{'q5'};?></h4>

<p class="fleche"><img src="/images/fleche.png" width="20px"></p>
<h5><?php echo $parsed_json->{$langue}->{'questionnaire'}->{'h5quest'};?></h5>
                            <p>
                                <input type="radio" name="q4" id="q4_bad" value="Badly"/> <?php echo $parsed_json->{$langue}->{'questionnaire'}->{'answergreat'};?></br>
                                <input type="radio" name="q4" id="q4_fine" value="Fine"/> <?php echo $parsed_json->{$langue}->{'questionnaire'}->{'answerfine'};?></br>
                                <input type="radio" name="q4" id="q4_well" value="Well"/> <?php echo $parsed_json->{$langue}->{'questionnaire'}->{'answerfinebut'};?></br>
                                <input type="radio" name="q4"id="q4_vwell" value="Very well"/> <?php echo $parsed_json->{$langue}->{'questionnaire'}->{'answerbad'};?>
                            </p> 
                        </div>
                        <br />

                        <div class="questionnaire">
                        <h4><?php echo $parsed_json->{$langue}->{'questionnaire'}->{'q6'};?></h4>

<p class="fleche"><img src="/images/fleche.png" width="20px"></p>
                            <p>
                                <input type="radio" name="q5" id="q5_vdiff" value="Very difficult"/> <?php echo $parsed_json->{$langue}->{'questionnaire'}->{'answerverydifficult'};?></br> 
                                <input type="radio" name="q5" id="q5_diff" value="Difficult"/> <?php echo $parsed_json->{$langue}->{'questionnaire'}->{'answerdifficult'};?></br> 
                                <input type="radio" name="q5" id="q5_regu" value="Regular"/> <?php echo $parsed_json->{$langue}->{'questionnaire'}->{'answerregular'};?></br>
                                <input type="radio" name="q5"id="q5_easy" value="Easy"/> <?php echo $parsed_json->{$langue}->{'questionnaire'}->{'answereasy'};?></br>
                                <input type="radio" name="q5"id="q5_veasy" value="Very easy"/> <?php echo $parsed_json->{$langue}->{'questionnaire'}->{'answerveryeasy'};?>
                            </p> 
                        </div>
                        <br />       
                        
                        <div class="questionnaire">
                        <h4><?php echo $parsed_json->{$langue}->{'questionnaire'}->{'q7'};?></h4>

<p class="fleche"><img src="/images/fleche.png" width="20px"></p>
                         
<div class="slider_avis">
            <p>1</p>
              <input type="range" name="q6"class="slidder" step="1" min="1" max="10" value="5" required>
            <p>10</p>
          </div>
                            </p> 
                        </div>
                        <br />   
                        
                        <?php $description = $parsed_json->{$langue}->{'questionnaire'}->{'answer'};?>

                        <div class="questionnaire">
                        <h4><?php echo $parsed_json->{$langue}->{'questionnaire'}->{'q8'};?></h4>

<p class="fleche"><img src="/images/fleche.png" width="20px"></p>
                        <p><textarea cols="70" rows="4" name="changeproduct" placeholder="<?php echo htmlspecialchars($description, ENT_QUOTES, 'UTF-8');?>"></textarea></p>
                        </div>
                        <br /> 
                        
                        <div class="questionnaire">
                        <h4><?php echo $parsed_json->{$langue}->{'questionnaire'}->{'q9'};?></h4>

<p class="fleche"><img src="/images/fleche.png" width="20px"></p>
                        <p><textarea cols="70" rows="4" name="changecustom" placeholder="<?php echo htmlspecialchars($description, ENT_QUOTES, 'UTF-8');?>"></textarea></p>
                        </div>
                        <br /> 

                        <div class="questionnaire">
                        <p><button type="submit" value="Submit"><?php echo $parsed_json->{$langue}->{'quizz'}->{'valider'};?> >></button></p>
                        </div>

</form>
                        <br /><br />

</article>
                    
                </section>

        <!--PIED DE LA PAGE-->
        <?php 
            include 'footer.php';
        ?>
 </body>
</html>
