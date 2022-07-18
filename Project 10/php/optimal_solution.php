<?php
    
    $modules = file_get_contents("OptimalSolution_Customer_1.json"); // On récupère le fichier de transition et on le parse
    $parsed_modules = json_decode($modules, true);
    
    if ($parsed_modules['selected_module_instances'][2]=="M32" || $parsed_modules['selected_module_instances'][2]=="M34") $_SESSION['outsole']=1;
    else if ($parsed_modules['selected_module_instances'][2]=="M31") $_SESSION['outsole']=2;
    else echo $_SESSION['outsole']=3;
    
    
    if ($parsed_modules['selected_module_instances'][5]=="M61" || $parsed_modules['selected_module_instances'][5]=="M63" || $parsed_modules['selected_module_instances'][5]=="M66") $_SESSION['heel']=1;
    else if ($parsed_modules['selected_module_instances'][5]=="M62" || $parsed_modules['selected_module_instances'][5]=="M64") $_SESSION['heel']=2;
    else $_SESSION['heel']=3;
    
?>

