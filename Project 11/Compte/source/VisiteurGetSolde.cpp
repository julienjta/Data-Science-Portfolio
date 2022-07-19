#include "../header/CompteManager.h"
/**
    @file VisiteurGetSolde.cpp
    @brief Définition des fonctions membres de la classe VisiteurGetSolde.
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/

void VisiteurGetSolde::visiter(CompteReel& _c) noexcept{
    solde += _c.getDernierMemento()->getSolde();
}

void VisiteurGetSolde::visiter(CompteVirtuel& _c) noexcept{
    for(auto it : _c.getFils()) {
        it->accepte(*this);
    }
}
