<?php 
    include 'traduction.php';
?>
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8" />
    <title><?php echo $parsed_json->{$langue}->{'index'}->{'titre'};?></title>
    <link rel="stylesheet" href="css/mystyle.css">
    </head>

    <body>
    <!--HAUT DE LA PAGE-->
        <?php 
            include 'header.php';
        ?>

    <!--Lien pour le quiz-->
                        
        <a class="link" href="/quizz.php"><img src="/images/quiz.png" width="50"><p><?php echo $parsed_json->{$langue}->{'index'}->{'debuter_quizz'};?></p></a>

    <!--CORPS DE LA PAGE-->
        <section>
            <article>
                <div class="parallax1"><h2><?php echo $parsed_json->{$langue}->{'index'}->{'titre_descr'};?></h2></div>
                    <div class="container"><div class="contenu">
                        <p class="questions"><img src="/images/question.jpg" height="60" /><span><?php echo $parsed_json->{$langue}->{'index'}->{'questions'};?></span></p>
                        <p><?php echo $parsed_json->{$langue}->{'index'}->{'text_descr'};?></p>
                    </div>
                </div>
                
            </article>
            <br />
            <article>
                <div class="parallax2"><h2><?php echo $parsed_json->{$langue}->{'index'}->{'titre_but'};?></h2></div>
                <div class="container">
                    <div class="contenu"><?php echo $parsed_json->{$langue}->{'index'}->{'text_but'};?></div>
                </div>
            </article>
            <br />
        
            <article>
                <div class="parallax3"><h2><?php echo $parsed_json->{$langue}->{'index'}->{'titre_real'};?></h2></div>
            </article>
            <br />
        </section>
    
    <!--PIED DE LA PAGE-->
        <?php 
            include 'footer.php';
        ?>
 </body>
</html>


