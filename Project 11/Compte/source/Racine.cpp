/**
    @file Racine.cpp
    @brief Définition des fonctions membres de la classe Racine.
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/
#include "../header/Racine.h"

Racine Racine::instance;

void Racine::debiter(double *_solde, double _montant) const{
    throw ExceptionComptabilite("[!]Impossible de débiter le compte racine !",
                                ExceptionComptabilite::CodeExcepComptabilite::ROOT_EXC_C);
}

void Racine::crediter(double *_solde, double _montant) const{
    throw ExceptionComptabilite("[!]Impossible de créditer le compte racine !",
                                ExceptionComptabilite::CodeExcepComptabilite::ROOT_EXC_C);
}
