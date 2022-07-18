<!--DOCUMENT PERMETTANT D'INSERER LE HAUT DE PAGE SUR L'INTEGRALITE DES PAGES DU SITE-->

<header>
    <p class="gear"><img src="images/gear.png" height="400px" width="400px" /></p> <!--Image de l'engrenage-->
    <div class="logo"> <!--Ensemble avec le logo et le nom du site-->
        <img src="images/shoe.png" height="30"  />
        <h1><?php echo $parsed_json->{$langue}->{'header'}->{'titre'};?></h1>
    </div>
    <nav> <!--Contient le sélecteur de langue-->
        <?php
            if ($langue=="fr")
            {
                echo " <p class=\"change\">Changer la langue</p><form action=\"".$_SERVER['PHP_SELF']."\" method=\"post\"> 
                       <input type=\"hidden\" name=\"langue\" value=\"eng\" /><input type=\"image\" value=\"Anglais\" src=\"/images/eng.png\" /> </form>"; 
            }
            else
            {
                echo " <p class=\"change\">Switch the language</p><form action=\"".$_SERVER['PHP_SELF']."\" method=\"post\">
                <input type=\"hidden\" name=\"langue\" value=\"fr\" /><input type=\"image\" value=\"French\" src=\"/images/fr.png\" /> </form>";
            }
        ?>
    </nav>
</header>