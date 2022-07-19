#include "../header/CompteManager.h"
/**
    @file visiteurlistecompte.cpp
    @brief Définition des fonctions membres de la classe visiteurlistecompte.
    @author Jérémy Godde d'après un modèle de Simon Lepage
    @version v1
    @date 23 mai 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/

void VisiteurListeCompte::visiter(CompteReel& _c) noexcept{
    if(seul_reel != 0)
        fillListe(_c);
}

void VisiteurListeCompte::visiter(CompteVirtuel& _c) noexcept{
    if(seul_reel != 1)
        fillListe(_c);
    for(auto it : _c.getFils()) it->accepte(*this);
}

void VisiteurListeCompte::fillListe(CompteHierarchie& _c) noexcept{
    liste->push_back(QString::fromStdString(_c.toString()));
    liste_id->push_back(_c.getId());
}
