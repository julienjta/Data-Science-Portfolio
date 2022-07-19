#ifndef VISITEURFREE_H_INCLUDED
#define VISITEURFREE_H_INCLUDED

/**
    @file VisiteurFree.h
    @brief VisiteurFree est un visiteur qui permet de libérer la mémoire dans des comptes.
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/

#include "../header/VisiteurPoste.h"

/**
    @class VisiteurFree "VisiteurFree.h"
    @brief VisiteurFree est un visiteur qui permet de libérer la mémoire dans des comptes.
*/

class VisiteurFree : public Visiteur{
    friend CompteManager;

public:
    /**
        @fn void VisiteurFree::visiter (CompteReel& _c) noexcept override;
        @brief Méthode qui permet de libérer la mémoire associée à un CompteReel.
        @param _c : CompteReel& _c,CompteReel auquel le visiteur veut avoir accés pour libérer sa mémoire.
    */
    void visiter(CompteReel& _c) noexcept override;
    /**
        @fn void VisiteurFree::visiter(CompteVirtuel& _c) noexcept override;
        @brief Méthode qui permet de libérer la mémoire associée à un CompteVirtuel ainsi que la mémoire utilisée par ses fils.
        @param _c : CompteVirtuel& _c,CompteVirtuel auquel le visiteur veut avoir accés pour libérer sa mémoire et celle de ses fils.
    */
    void visiter(CompteVirtuel& _c) noexcept override;

private:
    /**
        @fn VisiteurFree::VisiteurFree();
        @brief Constructeur privé
    */
    VisiteurFree() = default;

    /**
        @fn  VisiteurFree::VisiteurFree(const VisiteurFree& _v);
        @brief Constructeur par recopie privé.
        @param _v : const VisiteurFree&, référence constante sur le VisiteurFree à recopier.
    */
    VisiteurFree (const VisiteurFree& _v) = default;

    /**
        @fn  VisiteurFree& VisiteurFree::operator=(const VisiteurFree& _v);
        @brief Suprresion de surcharge de l'opérateur d'affectation privé.
        @param _v : const VisiteurFree&, référence constante sur le VisiteurFree à affecter.
    */
    VisiteurFree& operator=(const VisiteurFree& _v) = delete;
};

#endif // VISITEURFREE_H_INCLUDED
