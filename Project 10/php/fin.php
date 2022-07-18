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
            <div class="end">
                <div>
                    <img src="images/fin4.png" id="image_fin" width="130" height="130"/>
                </div>
                <div id="phrase_fin">
                    <?php echo $parsed_json->{$langue}->{'fin'}->{'fin1'};?></br></br>
                </div>
            </div></br>
            
            <center>
                    <FONT size="4">
                        <?php echo $parsed_json->{$langue}->{'fin'}->{'fin2'};?></br>
                        <?php echo $parsed_json->{$langue}->{'fin'}->{'fin3'};?><a href="/more.php" style="color:rgb(0,128,0);"/>more</a>
                
                        </br></br></br>
                        
                        <h5 id="couleur2">
                            <?php echo $parsed_json->{$langue}->{'fin'}->{'fin4'};?></br>
                            <?php echo $parsed_json->{$langue}->{'fin'}->{'fin5'};?>
                         </h5>
                    </FONT>
                   
                <img src="images/logo_utc.jpg" width="150" height="70" style="margin:30px"/>
                <img src="images/logo_anr.jpg" width="100" height="100" style="margin:30px"/>
                <img src="images/iprod.png" width="150" height="70" style="margin:30px"/>
                
                </br></br>
        </center>
                    
        </section>

        <!--PIED DE LA PAGE-->
        <?php 
            include 'footer.php';
        ?>
 </body>
</html>
