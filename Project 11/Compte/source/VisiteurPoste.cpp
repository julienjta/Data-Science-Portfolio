/**
    @file VisiteurPoste.cpp
    @brief Définition des fonctions membres de la classe VisiteurPoste.
    @author Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning COMPILE
*/
#include "../header/CompteManager.h"


void VisiteurPoste::visiter(CompteReel& _c) noexcept{
    if(_c.getPoste() == p) {
            resultat.insert(resultat.begin(),&_c);
    }
}

void VisiteurPoste::visiter(CompteVirtuel& _c) noexcept{
    // Si le compte n'est pas du poste cherché, et que ce n'est pas la racine,
    // pas besoin de chercher dans ses fils.
    if(_c.getPoste() != p && _c.getPoste() != RACINE) return;

    for(auto it : _c.getFils()){
        it->accepte(*this);
    }
}
