#ifndef VISITEURPOSTE_H_INCLUDED
#define VISITEURPOSTE_H_INCLUDED

/**
    @file VisiteurPoste.h
    @brief VisiteurPoste est un visiteur qui permet de récupérer une liste de tous les comptes réels d'un poste.
    @author Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning COMPILE
*/

#include "../header/Visiteur.h"

/**
    @class VisiteurPoste "VisiteurPoste.h"
    @brief VisiteurPoste est un visiteur qui permet de récupérer une liste de tous les comptes réels d'un poste.
*/

class VisiteurPoste : public Visiteur{
    friend CompteManager;
public:
    /**
        @fn void VisiteurPoste::visiter(CompteReel& _c)noexcept override;
        @brief Méthode qui permet de vérifier si un CompteReel est du poste recherché
        @param _c : CompteReel& _c, CompteReel auquel le visiteur veut avoir accés pour le comparer au poste recherché.
    */
    void visiter(CompteReel& _c) noexcept override;

    /**
        @fn void VisiteurPoste::visiter(CompteVirtuel& _c) noexcept override;
        @brief Méthode qui permet de recherche un Compte parmis les fils du compte passé en paramètre.
        @param _c : CompteVirtuel& _c, CompteVirtuel auquel le visiteur veut avoir accés pour comparer ses fils au poste cherché.
    */
    void visiter(CompteVirtuel& _c) noexcept override;

    /**
        @fn std::list<CompteHierarchie*> VisiteurPoste::getResultat() const noexcept;
        @brief Méthode qui permet d'obtenir la liste des comptes de ce poste.
        @return Une liste contenant les comptes de ce poste.
    */
    std::list<CompteHierarchie*> getResultat() const noexcept {return resultat;}

    /**
        @fn void VisiteurPoste::changePoste(Poste _p) noexcept;
        @brief Permet de changer le poste recherché.
    */
    void changePoste(Poste _p) noexcept {p = _p; resultat.clear();}

private:
    /**
        @var int VisiteurPoste::idcompte
        @brief Poste recherché
    */
    Poste p;
    /**
        @var CompteHierarchie VisiteurPoste::resultat
        @brief Liste des comptes correspondants.
    */
    std::list<CompteHierarchie*> resultat;

    /**
        @fn VisiteurPoste::VisiteurPoste() noexcept;
        @brief Constructeur privé
    */
    VisiteurPoste(Poste _p) noexcept : p(_p){}
    /**
        @fn  VisiteurPoste::VisiteurPoste(const VisiteurPoste& _v);
        @brief Constructeur par recopie privé
        @param _v : const VisiteurPoste&, référence constante sur le VisiteurPoste à recopier.
    */
    VisiteurPoste(const VisiteurPoste& _v) = default;

    /**
        @fn  VisiteurPoste& VisiteurPoste::operator=(const VisiteurPoste& _v);
        @brief Suprresion surcharge de l'opérateur d'affectation privé
        @param _v : const VisiteurPoste&, référence constante sur le VisiteurPoste à affecter.
    */
    VisiteurPoste& operator=(const VisiteurPoste& _v) = delete;
};



#endif // VISITEURPOSTE_H_INCLUDED
