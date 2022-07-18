<?php
    
    $functions = file_get_contents("selected_functions.json"); // On récupère le fichier de transition et on le parse
    $parsed_functions = json_decode($functions, true);
        
        $parsed_functions['selected_idx'] = array();
    
    if($_SESSION['test_fait']==on){
        
        $parsed_functions['customer_id']=$parsed_functions['customer_id']+1;
        
    if ($_POST['indoor']==on)$_SESSION['indoor']=on;
    else if ($_POST['indoor']=='') $_SESSION['indoor']=off;
       if ($_POST['outdoor']==on)$_SESSION['outdoor']=on;
   else if ($_POST['outdoor']=='') $_SESSION['outdoor']=off;
       if ($_POST['nature']==on)$_SESSION['nature']=on;
    else if ($_POST['nature']=='') $_SESSION['nature']=off;
       
       if ($_POST['winter']==on)$_SESSION['winter']=on;
     else if ($_POST['winter']=='') $_SESSION['winter']=off;
       if ($_POST['summer']==on)$_SESSION['summer']=on;
     else if ($_POST['summer']=='') $_SESSION['summer']=off;
       if ($_POST['rainy']==on)$_SESSION['rainy']=on;
        else if ($_POST['rainy']=='') $_SESSION['rainy']=off;
       
       if ($_POST['poids']==100)$_SESSION['poids']=100;
       else if ($_POST['poids']==50)$_SESSION['poids']=50;
       else if ($_POST['poids']==0)$_SESSION['poids']=0;
       
       if ($_POST['confort']==0)$_SESSION['confort']=0;
       else if ($_POST['confort']==50)$_SESSION['confort']=50;
       else if ($_POST['confort']==100)$_SESSION['confort']=100;
       
       if ($_POST['jogger']==on)$_SESSION['jogger']=on;
    else if ($_POST['jogger']=='') $_SESSION['jogger']=off;
       if ($_POST['trail']==on)$_SESSION['trail']=on;
    else if ($_POST['trail']=='') $_SESSION['trail']=off;
       if ($_POST['hiker']==on)$_SESSION['hiker']=on;
    else if ($_POST['hiker']=='') $_SESSION['hiker']=off;
       if ($_POST['walker']==on)$_SESSION['walker']=on;
    else if ($_POST['walker']=='') $_SESSION['walker']=off;
       
       if ($_POST['breathe']==on)$_SESSION['breathe']=on;
    else if ($_POST['breathe']=='') $_SESSION['breathe']=off;
       if ($_POST['waterp']==on)$_SESSION['waterp']=on;
    else if ($_POST['waterp']=='') $_SESSION['waterp']=off;
       if ($_POST['anckle']==on)$_SESSION['anckle']=on;
    else if ($_POST['anckle']=='') $_SESSION['anckle']=off;
       if ($_POST['waterr']==on)$_SESSION['waterr']=on;
    else if ($_POST['waterr']=='') $_SESSION['waterr']=off;
       if ($_POST['moisture']==on)$_SESSION['moisture']=on;
    else if ($_POST['moisture']=='') $_SESSION['moisture']=off;
       
       if ($_POST['foot_width']==narrow) $_SESSION['foot_width']=narrow;
       else if ($_POST['foot_width']==medium)$_SESSION['foot_width']=medium;
       else if ($_POST['foot_width']==wide)$_SESSION['foot_width']=wide;
       
       if ($_POST['stride']==neutral)$_SESSION['stride']=neutral;
       else if ($_POST['stride']==overpronated)$_SESSION['stride']=overpronated;
       else if ($_POST['stride']==supinated)$_SESSION['stride']=supinated;
    
        
        $_SESSION['test_fait']=off;
    }
    
    
    
    
    
    if ($_SESSION['indoor']==on)array_push($parsed_functions['selected_idx'], 1);
    if ($_SESSION['outdoor']==on)array_push($parsed_functions['selected_idx'], 2);
    if ($_SESSION['nature']==on)array_push($parsed_functions['selected_idx'], 3);
    
    if ($_SESSION['winter']==on)array_push($parsed_functions['selected_idx'], 4);
    if ($_SESSION['summer']==on)array_push($parsed_functions['selected_idx'], 5);
    if ($_SESSION['rainy']==on)array_push($parsed_functions['selected_idx'], 6);
    
    
    if ($_SESSION['poids']==100)array_push($parsed_functions['selected_idx'], 7);
    else if ($_SESSION['poids']==50)array_push($parsed_functions['selected_idx'], 8);
    else if ($_SESSION['poids']==0)array_push($parsed_functions['selected_idx'], 9);
    
    if ($_SESSION['confort']==0)array_push($parsed_functions['selected_idx'], 10);
    else if ($_SESSION['confort']==50)array_push($parsed_functions['selected_idx'], 11);
    else if ($_SESSION['confort']==100)array_push($parsed_functions['selected_idx'], 12);
    
    if ($_SESSION['jogger']==on)array_push($parsed_functions['selected_idx'], 13);
    if ($_SESSION['trail']==on)array_push($parsed_functions['selected_idx'], 14);
    if ($_SESSION['hiker']==on)array_push($parsed_functions['selected_idx'], 15);
    if ($_SESSION['walker']==on)array_push($parsed_functions['selected_idx'], 16);
    
    if ($_SESSION['breathe']==on)array_push($parsed_functions['selected_idx'], 17);
    if ($_SESSION['waterp']==on)array_push($parsed_functions['selected_idx'], 18);
    if ($_SESSION['anckle']==on)array_push($parsed_functions['selected_idx'], 19);
    if ($_SESSION['waterr']==on)array_push($parsed_functions['selected_idx'], 20);
    if ($_SESSION['moisture']==on)array_push($parsed_functions['selected_idx'], 21);
    
    if ($_SESSION['foot_width']==narrow)array_push($parsed_functions['selected_idx'],22);
    else if ($_SESSION['foot_width']==medium)array_push($parsed_functions['selected_idx'], 23);
    else if ($_SESSION['foot_width']==wide)array_push($parsed_functions['selected_idx'], 24);
    
    if ($_SESSION['stride']==neutral)array_push($parsed_functions['selected_idx'],25);
    else if ($_SESSION['stride']==overpronated)array_push($parsed_functions['selected_idx'], 26);
    else if ($_SESSION['stride']==supinated)array_push($parsed_functions['selected_idx'], 27);
    
    file_put_contents("selected_functions.json", json_encode($parsed_functions)); // On encore le fichier mise à jour et parsé et on le charge
?>
