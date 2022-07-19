/**
    @file VisiteurRecherche.cpp
    @brief Définition des fonctions membres de la classe VisiteurRecherche.
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/
#include "../header/CompteManager.h"

void VisiteurRecherche::visiter(CompteReel& _c) noexcept{
    if(_c.getId() == idcompte) {
        resultat = &_c ;
    }else if (_c.getNom()==nomcompte){
        resultat = &_c;
    }
}

void VisiteurRecherche::visiter(CompteVirtuel& _c) noexcept {
    if(_c.getId() == idcompte){
        resultat = &_c;
    }else if (_c.getNom()==nomcompte){
        resultat= &_c;
    } else{
        for(auto it : _c.getFils()){
            it->accepte(*this);
            if(resultat) return;
        }
    }
}
