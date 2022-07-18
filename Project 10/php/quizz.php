<!DOCTYPE html>

<?php 
    include 'traduction.php';
    
    session_start();
    
     $_SESSION['test_fait']=on;
?>

<html>
    <head>
      <title><?php echo $parsed_json->{$langue}->{'quizz'}->{'titre'};?></title>
      <link rel="stylesheet" href="css/mystyle.css"> 
    </head>

    <body>

    <!--TOP OF THE PAGE-->

       <?php 
            include 'header.php';
        ?>

    <!--BODY OF THE PAGE-->

    <div class="corps">

        <div class="stepper"> <!--Stepper to show the step (1, 2, 3)-->
            <div class="step--1 step-active"><?php echo $parsed_json->{$langue}->{'quizz'}->{'step1'};?></div>
            <div class="step--2 "><?php echo $parsed_json->{$langue}->{'quizz'}->{'step2'};?></div>
            <div class="step--3"><?php echo $parsed_json->{$langue}->{'quizz'}->{'step3'};?></div>
        </div>
        

        <!--Step 1: the runner-->
        <form method=post action="questionnaire.php">
        <div class="formq form-active">
            <div class="form--header-container"> <!--title and subtitle-->
                <h1 class="form--header-title">
                    <?php echo $parsed_json->{$langue}->{'quizz'}->{'titre_runner'};?>
                </h1>    
                <p class="form--header-text"><?php echo $parsed_json->{$langue}->{'quizz'}->{'titre_runner_descr'};?></p>
            </div>    


            <h3><?php echo $parsed_json->{$langue}->{'quizz'}->{'sous_titre_runner1'};?></h3> <!--Question 1/3-->
            <h4><?php echo $parsed_json->{$langue}->{'quizz'}->{'sous_titre_runner1.2'};?></h4> <!--Indicate that several options possible-->

            <!--Error if no option chosen-->
            <p id="check1text" style="visibility:hidden;color:red;"><?php echo $parsed_json->{$langue}->{'quizz'}->{'erreur'};?></p>

            <div class="runner1"  id="check1">

              <!--First option-->
              <div class="elem"> 
                <p id="image_jogger">
                <img src="/images/coureur.png" width="80" id="image_jogger" style="padding:2px; cursor:pointer; border:1px solid transparent;" onclick="cocheImage('jogger')" ></p>
                 <input class="groupcheckbox" type="checkbox" name="jogger" id="data_jogger" /> <label for="jogger"><?php echo $parsed_json->{$langue}->{'quizz'}->{'text_runner1'};?></label>
              </div>  

              <!--Second option-->
              <div class="elem">
                <p id="image_trailer"><img src="/images/traileur.png" width="100" id="image_trailer" style="padding:2px; cursor:pointer; border:1px solid transparent;" onclick="cocheImage('trailer')"></p>
                <input class="groupcheckbox" type="checkbox" name="trail" id="data_trailer" /> <label for="trail"><?php echo $parsed_json->{$langue}->{'quizz'}->{'text_runner2'};?></label>
              </div>
              <!--Third option-->
              <div class="elem">
                 <p id="image_hiker"><img src="/images/rando.png"  width="90" id="image_hiker" style="padding:2px; cursor:pointer; border:1px solid transparent;" onclick="cocheImage('hiker')"></p>
                 <input class="groupcheckbox" type="checkbox" name="hiker" id="data_hiker" /> <label for="trail"><?php echo $parsed_json->{$langue}->{'quizz'}->{'text_runner3'};?></label>
              </div>

              <!--Fourth option-->
              <div class="elem">
                 <p id="image_walker"><img src="/images/marche.jpg" width="110" id="image_walker" style="padding:2px; cursor:pointer; border:1px solid transparent;" onclick="cocheImage('walker')"></p>
                  <input class="groupcheckbox" type="checkbox" name="walker" id="data_walker" /> <label for="walker"><?php echo $parsed_json->{$langue}->{'quizz'}->{'text_runner4'};?></label>

              </div>
               
            </div> 

    <!--Function to change the borders of an icon selected-->
    <script type="text/javascript"> 
      function cocheImage(id)
      {
        if(document.getElementById('data_'+id).checked) //already an option chosen
        {
          document.getElementById('data_'+id).checked = false; //uncheck the option
          document.getElementById('image_'+id).style.border = '2px solid black';
            
            if(document.getElementById('data_supinated').checked==false && document.getElementById('data_neutral').checked==false && document.getElementById('data_overpronated').checked==false)
            {
              document.getElementById('data_'+id).checked = true;
              document.getElementById('image_'+id).style.border = '6px solid green';  
            }

            if(document.getElementById('data_wide').checked==false && document.getElementById('data_medium').checked==false && document.getElementById('data_narrow').checked==false)
            {
              document.getElementById('data_'+id).checked = true;
              document.getElementById('image_'+id).style.border = '6px solid green';
            }

       }

          else
          {
            document.getElementById('data_'+id).checked = true;
            document.getElementById('image_'+id).style.border = '6px solid green';
            
              
            /*Control here that only one element of the radio is checked*/
            if(id=='overpronated')
            {
              document.getElementById('image_supinated').style.border = '2px solid black';
              document.getElementById('image_neutral').style.border = '2px solid black';
            }

            if(id=='supinated')
            {
              document.getElementById('image_overpronated').style.border = '2px solid black';
              document.getElementById('image_neutral').style.border = '2px solid black';
            }

            if(id=='neutral')
            {
              document.getElementById('image_supinated').style.border = '2px solid black';
              document.getElementById('image_overpronated').style.border = '2px solid black';
            }
              
              
              
            if(id=='narrow')
            {
              document.getElementById('image_medium').style.border = '2px solid black';
              document.getElementById('image_wide').style.border = '2px solid black';
            }

            if(id=='medium')
            {
              document.getElementById('image_narrow').style.border = '2px solid black';
              document.getElementById('image_wide').style.border = '2px solid black';
            }

            if(id=='wide')
            {
              document.getElementById('image_narrow').style.border = '2px solid black';
              document.getElementById('image_medium').style.border = '2px solid black';
            }

          }
          return false;
      }  

    </script> 

            <br />
            
            <!--Question 2/3-->
            <h3><?php echo $parsed_json->{$langue}->{'quizz'}->{'sous_titre_runner2'};?></h3>
            <div class="runner2">
             
                <!--First option -->
                <div class="elem">
                  <p id="image_overpronated"><img src="/images/pronation.png" width="90" id="image_overpronated" style="padding:2px; cursor:pointer; border:1px solid transparent;" onclick="cocheImage('overpronated')"></p>
                  <input type="radio" required name="stride" value="overpronated" id="data_overpronated" /> <label for="overpronated"><?php echo $parsed_json->{$langue}->{'quizz'}->{'text_runner6'};?></label>
                </div>  
              
                <!--Second option-->
                <div class="elem">
                  <p id="image_neutral">
                  <img src="/images/neutre.png" width="90" id="image_neutral" style="padding:2px; cursor:pointer; border:1px solid transparent;" onclick="cocheImage('neutral')" ></p>
                  <input type="radio" required name="stride" value="neutral" id="data_neutral"/> <label for="neutral"><?php echo $parsed_json->{$langue}->{'quizz'}->{'text_runner5'};?></label>
                </div>
              
                <!--Third option-->  
                <div class="elem">
                  <p id="image_supinated"><img src="/images/supination.png"  width="100" id="image_supinated" style="padding:2px; cursor:pointer; border:1px solid transparent;" onclick="cocheImage('supinated')"></p>
                  <input type="radio" required name="stride" value="supinated" id="data_supinated" /> <label for="supinated"><?php echo $parsed_json->{$langue}->{'quizz'}->{'text_runner7'};?></label>
                </div> 

                <!--By default, the option "stride type=neutral" is selected-->
                <script>cocheImage('neutral');</script>
            </div>
            
            
        
            <br />

            <!--Question 3/3-->
            <h3><?php echo $parsed_json->{$langue}->{'quizz'}->{'sous_titre_runner3'};?></h3/>
            <div class="runner3">

                <!--First option -->
                <div class="elem">           
                  <p id="image_narrow"><img src="/images/narrow.png" width="80" height="120" id="image_narrow" style="padding:2px; cursor:pointer; border:1px solid transparent;" onclick="cocheImage('narrow')"></p>
                  <input type="radio" required name="foot_width" value="narrow" id="data_narrow" /> <label for="narrow"><?php echo $parsed_json->{$langue}->{'quizz'}->{'text_runner8'};?></label>
                </div>

                <!--Second option -->
                <div class="elem">
                  <p id="image_medium"><img src="/images/medium.png" width="80" height="120"  id="image_medium" style="padding:2px; cursor:pointer; border:1px solid transparent;" onclick="cocheImage('medium')"></p>
                  <input type="radio" required name="foot_width" value="medium" id="data_medium" /> <label for="medium"><?php echo $parsed_json->{$langue}->{'quizz'}->{'text_runner9'};?></label>
                </div>

                <!--Third option-->
                <div class="elem">
                  <p id="image_wide"><img src="/images/wide.png"  width="80" height="120" id="image_wide" style="padding:2px; cursor:pointer; border:1px solid transparent;" onclick="cocheImage('wide')"></p>
                  <input type="radio" required name="foot_width" value="wide" id="data_wide"/> <label for="wide"><?php echo $parsed_json->{$langue}->{'quizz'}->{'text_runner10'};?></label>
                </div>

                <!--By default, the option "width=medium" is selected--> 
                <script>cocheImage('medium');</script>
            </div>


            <br />
        
        <!--Button to validate the first step of the quiz--> 
        <button class="form__btn" onclick="ctr1()" id="btn-1"><?php echo $parsed_json->{$langue}->{'quizz'}->{'btn_next'};?></button>
      
        <!--Function to check that at least 1 option selected for Q1 et 1 option selected for Q2 and Q3-->
        <script>
          function ctr1() /*Control that at least on element of the checkbox is checked*/
          {
            if (((document.getElementById("data_jogger").checked) || (document.getElementById("data_trailer").checked) || (document.getElementById("data_hiker").checked) || (document.getElementById("data_walker").checked))
              && ((document.getElementById("data_neutral").checked) || (document.getElementById("data_overpronated").checked) || (document.getElementById("data_supinated").checked)) && ((document.getElementById("data_narrow").checked) || (document.getElementById("data_medium").checked) || (document.getElementById("data_wide").checked)))
              {
               return true;
              } 

            else
              {       
                return false;
              }
          } 
    
          </script>


      </div>

      
       
        <!--Step 2: the run-->
        <div class="formq">

          <!--title and subtitle-->
          <div class="form--header-container">
              <h1 class="form--header-title"><?php echo $parsed_json->{$langue}->{'quizz'}->{'titre_run'};?></h1>
              <p class="form--header-text"><?php echo $parsed_json->{$langue}->{'quizz'}->{'titre_run_descr'};?></p>   
          </div>       
            
            <!--Question 1/2-->
            <h3> <?php echo $parsed_json->{$langue}->{'quizz'}->{'sous_titre_run1'};?></h3/>
            <!--Indicate that several options are possible-->
            <h4><?php echo $parsed_json->{$langue}->{'quizz'}->{'sous_titre_runner1.2'};?></h4>

              <!--Error message if no option selected for question 1-->
              <p id="check2text" style="visibility:hidden;color:red;"><?php echo $parsed_json->{$langue}->{'quizz'}->{'erreur'};?></p>
              <div id="check2" class="run1">
            
                <!--First option-->
                <div class="elem">
                  <p id="image_outdoor"><img src="/images/outdoor.png" alt="" width="80" id="image_outdoor"  style="padding:2px; cursor:pointer; border:1px solid transparent" onclick="cocheImage('outdoor')"></p>
                  <input type="checkbox" name="outdoor" id="data_outdoor" /> <label for="outdoor"><?php echo $parsed_json->{$langue}->{'quizz'}->{'text_run1'};?></label>
                </div>

                <!--Second option-->
                <div class="elem">
                  <p id="image_indoor"><img src="/images/indoor.png" alt="" width="80" id="image_indoor" style="padding:2px; cursor:pointer; border:1px solid transparent;" onclick="cocheImage('indoor')"></p>
                  <input type="checkbox" name="indoor" id="data_indoor"/> <label for="indoor"><?php echo $parsed_json->{$langue}->{'quizz'}->{'text_run2'};?></label> 
                </div>

                <!--Third option-->
                <div class="elem">
                  <p id="image_nature"><img src="/images/arbre.jpg" alt="" width="80" id="image_nature" style="padding:2px; cursor:pointer; border:1px solid transparent;" onclick="cocheImage('nature')"></p>
                  <input type="checkbox" name="nature" id="data_nature" /> <label for="nature"><?php echo $parsed_json->{$langue}->{'quizz'}->{'text_run3'};?></label>
                </div>   
                
          </div>



          <br />

          <!--Question 2/2-->
          <h3><?php echo $parsed_json->{$langue}->{'quizz'}->{'sous_titre_run2'};?></h3>
          <!--Indicate that several options are possible-->
          <h4><?php echo $parsed_json->{$langue}->{'quizz'}->{'sous_titre_runner1.2'};?></h4>

          <!--Error message if no option selected for question 2-->
          <p id="check3text" style="visibility:hidden;color:red;"><?php echo $parsed_json->{$langue}->{'quizz'}->{'erreur'};?></p>
            
          <div  id="check3" class="run2">

              <!--Option 1-->
              <div class="elem">
                <p id="image_summer"><img src="/images/soleil.png" alt="" width="80" id="image_summer" style="padding:2px; cursor:pointer; border:1px solid transparent;" onclick="cocheImage('summer')" ></p>
                <input type="checkbox" name="summer" id="data_summer" /> <label for="summer"><?php echo $parsed_json->{$langue}->{'quizz'}->{'text_run5'};?></label>
              </div>

              <!--Option 2-->
              <div class="elem">
                <p id="image_rainy"><img src="/images/pluie.png" alt="" width="80" id="image_rainy" style="padding:2px; cursor:pointer; border:1px solid transparent;" onclick="cocheImage('rainy')"></p>
                <input type="checkbox" name="rainy" id="data_rainy" /> <label for="rainy"><?php echo $parsed_json->{$langue}->{'quizz'}->{'text_run4'};?></label>
              </div>

              <!--Option 3-->
              <div class="elem">
                <p id="image_winter"><img src="/images/neige.png" alt="" width="80" id="image_winter" style="padding:2px; cursor:pointer; border:1px solid transparent;" onclick="cocheImage('winter')"></p>
                <input type="checkbox" name="winter" id="data_winter" /> <label for="winter"><?php echo $parsed_json->{$langue}->{'quizz'}->{'text_run6'};?></label>     
              </div>

          </div>


          <br /><br />

          <!-- Button to step back to form 1/3-->
          <button class="form__btn" id="btn-2-prev"><?php echo $parsed_json->{$langue}->{'quizz'}->{'btn_previous'};?></button>
          <!-- Button to go to form 3/3-->
          <button class="form__btn" id="btn-2-next" onclick="ctr2()"><?php echo $parsed_json->{$langue}->{'quizz'}->{'btn_next'};?></button>


          <!--Function to check that at least 1 option selected for Q1 and Q2-->
          <script>
          function ctr2()
          {
            if (document.getElementById("data_outdoor").checked==false && document.getElementById("data_indoor").checked==false && document.getElementById("data_nature").checked==false && document.getElementById("data_summer").checked==false && document.getElementById("data_rainy").checked==false && document.getElementById("data_winter").checked==false) 
            {
              return 4; //no option selected for both questions
            }

            else if (document.getElementById("data_summer").checked==false && document.getElementById("data_rainy").checked==false && document.getElementById("data_winter").checked==false)
            {
              return 2; //no option selected for question 2
            }

            else if (!(document.getElementById("data_outdoor").checked || document.getElementById("data_indoor").checked || document.getElementById("data_nature").checked))
            {
              return 3; //no option selected for question 1
            }

            else  //at least one option selected for both questions --> OK
            {
                return 1;
            }

          } 
 
        </script>
        
      </div>

       
      <!--Step 3: the shoe-->
      <div class="formq">

        <!--Title and subtitle-->
        <div class="form--header-container">
          <h1 class="form--header-title"><?php echo $parsed_json->{$langue}->{'quizz'}->{'titre_shoe'};?> </h1>
          <p class="form--header-text"><?php echo $parsed_json->{$langue}->{'quizz'}->{'titre_shoe_descr'};?></p>
        </div> 


          <!--Question 1/3-->
          <h3><?php echo $parsed_json->{$langue}->{'quizz'}->{'sous_titre_shoe1'};?></h3>

          <div class="shoe1">

            <div class="options">
              <p><input type="checkbox" name="moisture" id="moisture" /> <label for="moisture"><?php echo $parsed_json->{$langue}->{'quizz'}->{'text_shoe1'};?></label></p>
              <p><input type="checkbox" name="waterr" id="waterr" /> <label for="waterr"><?php echo $parsed_json->{$langue}->{'quizz'}->{'text_shoe2'};?></label></p>
              <p><input type="checkbox" name="waterp" id="waterp" /> <label for="waterp"><?php echo $parsed_json->{$langue}->{'quizz'}->{'text_shoe3'};?></label></p>
              <p><input type="checkbox" name="breathe" id="breathe" /> <label for="breathe"><?php echo $parsed_json->{$langue}->{'quizz'}->{'text_shoe4'};?></label></p>
              <p><input type="checkbox" name="anckle" id="anckle" /> <label for="anckle"><?php echo $parsed_json->{$langue}->{'quizz'}->{'text_shoe5'};?></label></p>
            </div>

         </div>
            
        <br /><br />

          <!--Question 2/3-->
          <h3><?php echo $parsed_json->{$langue}->{'quizz'}->{'sous_titre_shoe2'};?></h3>

          <div class="shoe2">
            <p>-</p>
              <input class="slider" name="poids" type="range" min="0" max="100" value="50" step="50"  required />
            <p>+</p>
          </div>

          <br /><br />

          <!--Question 3/3-->
          <h3><?php echo $parsed_json->{$langue}->{'quizz'}->{'sous_titre_shoe3'};?></h3>

          <div class="shoe3">
            <p>-</p>
              <input class="slider" name="confort" type="range" min="0" max="100" value="50" step="50" required />
            <p>+</p>
          </div>  
        

          <br /><br />

          <!-- Button to step back to form 2/3-->
          <button class="form__btn" id="btn-3-prev"><?php echo $parsed_json->{$langue}->{'quizz'}->{'btn_previous'};?></button>
          <!-- Button validate the quiz-->
          <button type="submit" class="form__btn" id="btn-3"><?php echo $parsed_json->{$langue}->{'quizz'}->{'valider'};?></button>
        </div>
        </form>
    </div>

    <!--BOTTOM OF THE PAGE-->

    <?php 
      include 'footer.php';
    ?>

    <!-- Function which permits to go from one form of the quiz to an other-->
    <script type="text/javascript">

      //Function to change the active form
      const gotoNextform = (prev, next, stepPrev, stepNext) => 
      {
        const prevform = prev.parentElement
        const nextform = next.parentElement
        const nextStep = document.querySelector(`.step--${stepNext}`)
        const prevStep = document.querySelector(`.step--${stepPrev}`)

        //Change the activity/inactivity of the forms
        nextform.classList.add("form-active")
        nextform.classList.add("form-active-animate")
        prevform.classList.add("form-inactive")

        //Update the stepper
        prevStep.classList.remove("step-active")
        nextStep.classList.add("step-active")

        // Remove the active form
        setTimeout(() => 
        {
        prevform.classList.remove("form-active")
        prevform.classList.remove("form-inactive")
        nextform.classList.remove("form-active-animate")
        }, 500)
      }

      //Creation of a constante variable for each button
      const formBtn1 = document.querySelector("#btn-1")
      const formBtnPrev2 = document.querySelector("#btn-2-prev")
      const formBtnNext2 = document.querySelector("#btn-2-next")
      const formBtn3 = document.querySelector("#btn-3")
      const formBtnPrev3 = document.querySelector("#btn-3-prev")

      // Passage from form 1 to 2
      formBtn1.addEventListener("click", function(e) //if you click on the button next
      { 
        if (ctr1()==true) //at least one option selected for each question --> OK
        {
          document.getElementById('check1').style.border = 'none';
          document.getElementById('check1text').style.visibility = 'hidden';
          document.getElementById('check1text').style.display = 'none';
          e.preventDefault(); //no page web update not to going back to form 1
          gotoNextform(formBtn1, formBtnNext2, 1, 2); //passage
        }
        else //error
          { 
            document.getElementById('check1').style.border = '2px solid red'; //circle Q1 with red color
            document.getElementById('check1text').style.visibility = 'visible';
            document.getElementById('check1text').style.display = 'inline-block';             
            e.preventDefault() 
          }

        window.scrollTo(0, 0); //go to the top of the page
      })


      //Passage from Form 2 to form 3
      formBtnNext2.addEventListener("click", function(e) 
      {
        if (ctr2()==3) //no option selected for Q1
        {
          document.getElementById('check2').style.border = '2px solid red'; //circle Q1 with red color...
          document.getElementById('check2text').style.visibility = 'visible';
          document.getElementById('check2text').style.display = 'inline-block';
          document.getElementById('check3').style.border = 'none';         //...but not Q2
          document.getElementById('check3text').style.visibility = 'hidden ';
          document.getElementById('check3text').style.display = 'none';
          window.scrollTo(0, 0); //go back to the top of the page to see Q1
          e.preventDefault(); //no update to avoid to get back to form 1
        }

        else if (ctr2()==2) //no option selected for Q2
        {
          document.getElementById('check3').style.border = '2px solid red'; //circle Q2 with red color...
          document.getElementById('check2text').style.visibility = 'visible';
          document.getElementById('check3text').style.visibility = 'visible';
          document.getElementById('check3text').style.display = 'inline-block'; 
          document.getElementById('check2').style.border = 'none';          //...but not Q1
          document.getElementById('check2text').style.visibility = 'hidden ';
          document.getElementById('check2text').style.display = 'none';
          e.preventDefault();
        }

        else if  (ctr2()==4) //no option selected for both questions
        {
          document.getElementById('check2').style.border = '2px solid red'; //circle Q1 with red color...
          document.getElementById('check2text').style.visibility = 'visible';
          document.getElementById('check2text').style.display = 'inline-block';
          document.getElementById('check3').style.border = '2px solid red'; //... and Q2 too
          document.getElementById('check3text').style.visibility = 'visible';
          document.getElementById('check3text').style.display = 'inline-block';                      
          e.preventDefault();
          window.scrollTo(0, 0);
        }
      
        else //at least one option selected for both questions -->OK
        {
          document.getElementById('check3').style.border = 'none'; //no red cirle for Q1...
          document.getElementById('check3text').style.visibility = 'hidden ';
          document.getElementById('check3text').style.display = 'none';
          document.getElementById('check2').style.border = 'none';   //...Neither for Q2
          document.getElementById('check2text').style.visibility = 'hidden ';
          document.getElementById('check2text').style.display = 'none';
          e.preventDefault();
          gotoNextform(formBtnNext2, formBtn3, 2, 3); //passage to form 3
          window.scrollTo(0, 0);
        }                  
      })


      // Passage from form 2 to form 1
      formBtnPrev2.addEventListener("click", function(e) 
      {
        gotoNextform(formBtnNext2, formBtn1, 2, 1)
        window.scrollTo(0, 0);
        e.preventDefault()
      })

      //Passage du form 3 au form 2
      formBtnPrev3.addEventListener("click", function(e) 
      {
        gotoNextform(formBtnPrev3, formBtnPrev2, 3, 2)
        window.scrollTo(0, 0);
        e.preventDefault()
      })

    </script>    

 <!-- <script src= "js/formq.js" type="text/javascript"></script> -- >   
  </body>

</html>







