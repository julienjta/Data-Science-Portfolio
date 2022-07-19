/**
    @file CompteVirtuel.cpp
    @brief Définition des fonctions membres de la classe CompteVirtuel.
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 29 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/

#include "../header/CompteManager.h"


void CompteVirtuel::accepte(Visiteur& _v) noexcept{
    _v.visiter(*this);
}

//on regarde si le compte a des fils, s'il en a exception
void CompteVirtuel::supprimerCompte(){
    CompteManager &cm = CompteManager::getInstance();
    CompteHierarchie* pere = cm.getPere(this);
    if (getFils().size()==0){
        pere->supprimerFils(this);
        delete this;
    }else{
        throw ExceptionComptabilite("Tentative de suppression d'un CompteVirtuel qui contient d'autre comptes",
                                ExceptionComptabilite::CodeExcepComptabilite::SUPVIR_EXC_C);
    }
}

void CompteVirtuel::undo(Originator* _o){
    throw ExceptionComptabilite("Il est impossible de créditer, débiter ou rapprocher un CompteVirtuel",
                                ExceptionComptabilite::CodeExcepComptabilite::MEMV_EXC_C);
}

void CompteVirtuel::saveState(Originator _o){
    throw ExceptionComptabilite("Il est impossible de créditer, débiter ou rapprocher un CompteVirtuel",
                                ExceptionComptabilite::CodeExcepComptabilite::MEMV_EXC_C);
}

Memento* CompteVirtuel::getDernierMemento(){
    throw ExceptionComptabilite("Il est impossible de créditer, débiter ou rapprocher un CompteVirtuel",
                                ExceptionComptabilite::CodeExcepComptabilite::MEMV_EXC_C);
}



const list<Memento*>& CompteVirtuel::getMementos() const{
    throw ExceptionComptabilite("[!]Il est impossible de créditer, débiter ou rapprocher un CompteVirtuel",
                                ExceptionComptabilite::CodeExcepComptabilite::MEMV_EXC_C);
}
