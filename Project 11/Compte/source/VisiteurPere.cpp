/**
    @file VisiteurPere.cpp
    @brief Définition des fonctions membres de la classe VisiteurPere.
    @author Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/
#include "../header/CompteManager.h"

// Un compte réel ne peut pas être père
void VisiteurPere::visiter(CompteReel& _c) noexcept {
    return;
}

void VisiteurPere::visiter(CompteVirtuel& _c) noexcept {
    std::set<CompteHierarchie*> set_fils = _c.getFils();

    if(set_fils.find(recherche) != set_fils.end()){
        resultat = &_c;
    } else {
        for(auto it : set_fils){
            // On ne cherche que parmi les comptes de bon poste.
            // Pas besoin de vérifier si c'est la racine : dans le pire des cas
            // _c est la racine, et on cherche directement parmi ses fils.
            if(it->getPoste() == recherche->getPoste()){
                it->accepte(*this);
                if(resultat) return;
            }
        }
    }
}
