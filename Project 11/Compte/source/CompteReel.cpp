/**
    @file CompteReel.cpp
    @brief Définition des fonctions membres de la classe CompteReel.
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 29 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/
#include "../header/CompteManager.h"

void CompteReel::accepte(Visiteur& _v) noexcept{
    _v.visiter(*this);
}

const set<CompteHierarchie*> CompteReel::getFils() const{
    throw ExceptionHierarchie("[!]Impossible de récupérer les fils d'un compte réel.",
                               ExceptionHierarchie::CodeExcepHierarchie::FLSR_EXC_H);
}


void CompteReel::ajouterFils(CompteHierarchie* _c){
   throw ExceptionHierarchie("[!]Impossible d'ajouter un fils à un compte réel.",
                              ExceptionHierarchie::CodeExcepHierarchie::FLSR_EXC_H);
}

void CompteReel::supprimerFils(CompteHierarchie* _c){
   throw ExceptionHierarchie("[!]Impossible de retirer un fils à un compte réel.",
                              ExceptionHierarchie::CodeExcepHierarchie::FLSR_EXC_H);
}

void CompteReel::supprimerCompte(){
    CompteManager &cm = CompteManager::getInstance();
    CompteHierarchie* pere = cm.getPere(this);
    TransactionManager &c_trans_manager = TransactionManager::getInstance();

    if(c_trans_manager.emptyTransactionsParCompte(this->getId()))
    {
        pere->supprimerFils(this);
        delete this;
        return;
    }
    else
    {
        throw ExceptionComptabilite("[!]Impossible de retirer un compte qui a des transactions.",
                ExceptionComptabilite::CodeExcepComptabilite::SUPREL_EXC_C);
    }

}


 void CompteReel::undo(Originator* _o) noexcept {
    if (!mementos.size()){
        return;
    }
    Memento *memento = this->mementos.back();
    this->mementos.pop_back();

    _o->restoreMemento(*memento);
    //attraper exception sinon
}


CompteReel::~CompteReel() noexcept {
    while(mementos.size()){
        delete mementos.back();
        mementos.pop_back();
    }
}
