<!--DOCUMENT PERMETTANT D INSERER LE PIED DE PAGE SUR L INTEGRALITE DES PAGES DU SITE-->
<?php 
    include 'traduction.php';
?>
<footer>
    
    <ul>
        <li><a href="/more.php"><img width="20" height="20" src="/images/loupe.png"/><?php echo $parsed_json->{$langue}->{'footer'}->{'more'};?></a></li>
        <li><a href="mailto:shoe-customisator.rbv@utc.fr"><img width="22" height="22" src="/images/mail.png"/><?php echo $parsed_json->{$langue}->{'footer'}->{'contact'};?></a></li>
        <li><a href="/login.php"><img width="20" height="20" src="/images/login.png"/><?php echo $parsed_json->{$langue}->{'footer'}->{'connect'};?></a></li>
    </ul>
<p class="gear2"><img src="images/gear.png" height="380px" width="380px" /></p> <!--Image de l engrenage-->
    <p class="logo2"><img src="/images/shoe.png" height="40px"/></p>
</footer>
