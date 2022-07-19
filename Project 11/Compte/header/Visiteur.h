#ifndef VISITEUR_H_INCLUDED
#define VISITEUR_H_INCLUDED

/**
    @file Visiteur.h
    @brief Classe mères des différents visiteurs. Les visiteurs permettent de parcourir la hiérarchie des comptes.
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/

#include "../header/CompteHierarchie.h"

/**
    @class Visiteur "Visiteur.h"
    @brief Classe mères des différents visiteurs. Les visiteurs permettent de parcourir la hiérarchie des comptes.
*/
class Visiteur{
public:
    /**
        @fn virtual void visiter(CompteReel& _c) noexcept;
        @brief Méthode qui permet au visiteur de visiter un CompteReel.
        @param _c : CompteReel&, CompteReel auquel le visiteur veut avoir accés.
    */
    virtual void visiter(CompteReel& _c) noexcept = 0;
    /**
        @fn virtual void visiter(CompteVirtuel& _c) noexcept ;
        @brief Méthode qui permet au visiteur de visiter un CompteVirtuel.
        @param _c : CompteVirtuel&, CompteVirtuel auquel le visiteur veut avoir accés.
    */
    virtual void visiter(CompteVirtuel& _c) noexcept = 0;
};


#endif // VISITEUR_H_INCLUDED
