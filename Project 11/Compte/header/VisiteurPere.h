#ifndef VISITEURPERE_H_INCLUDED
#define VISITEURPERE_H_INCLUDED

/**
    @file VisiteurPere.h
    @brief VisiteurPere est un visiteur qui permet de trouver le père d'un compte
    @author Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/

#include "../header/VisiteurAffichage.h"

/**
    @class VisiteurPere "VisiteurPere.h"
    @brief VisiteurPere est un visiteur qui permet de trouver le père d'un compte.
*/

class VisiteurPere : public Visiteur{
    friend CompteManager;

public:
    /**
        @fn void VisiteurPere::visiter(CompteReel& _c) noexcept override;
        @brief Méthode pour les comptes réels. Ne fait rien car un compte réel ne peut pas être père.
        @param _c : CompteReel& _c
    */
    void visiter(CompteReel& _c) noexcept override;

    /**
        @fn void VisiteurPere::visiter(CompteVirtuel &_c) noexcept override;
        @brief Méthode qui permet de rechercher si le compte cherché est dans les fils.
        @param _c : CompteVirtuel& _c, CompteVirtuel auquel le visiteur veut avoir accés pour comparer ses fils au compte recherché.
    */
    void visiter(CompteVirtuel& _c) noexcept override;

    /**
        @fn CompteHierarchie* VisiteurPere::getResultat() const noexcept;
        @brief Méthode qui permet d'obtenir un pointeur sur le compte recherché s'il existe.
        @return Un pointeur sur le CompteHierarchie si le père existe, nullptr sinon.
    */
    CompteHierarchie* getResultat() const noexcept {return resultat;}
private:
    /**
        @var CompteHierarchie* VisiteurPere::recherche
        @brief Pointeur sur le compte recherché.
    */
    CompteHierarchie* recherche;
    /**
        @var CompteHierarchie VisiteurPere::resultat
        @brief Pointeur sur le compte recherché lorsqu'il a été trouvé.
    */
    CompteHierarchie* resultat;

      /**
        @fn VisiteurPere::VisiteurPere() noexcept;
        @brief Constructeur privé
    */
    VisiteurPere(CompteHierarchie* _recherche) noexcept : recherche(_recherche), resultat(nullptr){};

    /**
        @fn  VisiteurPere::VisiteurPere(const VisiteurPere& _v);
        @brief Constructeur par recopie privé
        @param _v : const VisiteurPere&, référence constante sur le VisiteurPere à recopier.
    */
    VisiteurPere(const VisiteurPere& _v) = default;

    /**
        @fn  VisiteurPere& VisiteurPere::operator=(const VisiteurPere& _v);
        @brief Supression surcharge de l'opérateur d'affectation privé
        @param _v : const VisiteurPere&, référence constante sur le VisiteurPere à affecter.
    */
    VisiteurPere& operator=(const VisiteurPere& _v) = delete;

};



#endif // VISITEURPERE_H_INCLUDED
