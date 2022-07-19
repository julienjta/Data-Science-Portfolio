/**
    @file VisiteurFree.cpp
    @brief Définition des fonctions membres de la classe VisiteurFree.
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/
#include "../header/CompteManager.h"

void VisiteurFree::visiter(CompteReel& _c) noexcept{
    delete &_c;
}
void VisiteurFree::visiter(CompteVirtuel& _c) noexcept{
    for(auto it : _c.getFils()){
        it->accepte(*this);
    }
    delete &_c;
}
