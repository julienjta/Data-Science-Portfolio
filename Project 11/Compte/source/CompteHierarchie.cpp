/**
    @file CompteHierarchie.cpp
    @brief Définition des fonctions membres de la classe CompteHierarchie
    @author Ophélie Delattre/ Simon Lepage
    @version v2
    @date 4 mai 2020
    @bug aucun détecté
    @warning COMPILE
    @note aucune
*/

#include "../header/CompteHierarchie.h"

string CompteHierarchie::toString() const noexcept{
    return poste->getLetter() + " : " + nom;
}
