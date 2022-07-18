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

    <!--CORPS DE LA PAGE-->
        <section>
            <article>
                </br>
                <div class="container"><div class="contenu">
                <p class="style-more"><img src="/images/mc.png" height="60" /><span><?php echo $parsed_json->{$langue}->{'more'}->{'mc'};?></span></p>
                </div></div>     
            </article>

            <article>
                </br>
                <div class="container"><div class="contenu">
                <p class="style-more"><span><?php echo $parsed_json->{$langue}->{'more'}->{'md'};?></span><img src="/images/md.png" height="60" /></p>
                </div></div>    
                
            </article>

            <article>
                </br>
                <div class="container"><div class="contenu">
                <p class="style-more"><img src="/images/smile.png" height="60" /><span><?php echo $parsed_json->{$langue}->{'more'}->{'smile'};?></span></p>
                </div></div>     
            </article>

            <article>
                </br>
                <div class="container"><div class="contenu">
                <p class="style-more"><img src="/images/puzzle.png" height="60" /><span><?php echo $parsed_json->{$langue}->{'more'}->{'puzzle'};?></span></p>
                </div></div>     
            </article>

            <article>
                </br>
                <div class="container"><div class="contenu">
                <p class="style-more"><img src="/images/interdit.png" height="60" /><span><?php echo $parsed_json->{$langue}->{'more'}->{'interdit'};?></span></p>
                </div></div>     
            </article>

            <article>
                </br>
                <div class="container">
                <p><img src="/images/iprod.png" height="110" /></span></p>
                </div>     
            </article>

            <article>
                <div class="container"><div class="contenu">
                <p><span><?php echo $parsed_json->{$langue}->{'more'}->{'more-descr'};?></span></p>
                </div></div>    
                
            </article>
            
        </section>
    
    <!--PIED DE LA PAGE-->
        <?php 
            include 'footer.php';
        ?>
 </body>
</html>
