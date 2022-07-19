#ifndef VISITEURRECHERCHE_H_INCLUDED
#define VISITEURRECHERCHE_H_INCLUDED
/**
    @file VisiteurRecherche.h
    @brief VisiteurRecherche est un visiteur qui permet de recherche un compte dans la hiérarchie des comptes
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/

#include "../header/VisiteurPere.h"

/**
    @class VisiteurRecherche "VisiteurRecherche.h"
    @brief VisiteurRecherhe est un visiteur qui permet de recherche un compte dans la hiérarchie des comptes.
*/

class VisiteurRecherche : public Visiteur{
    friend CompteManager;
public:
    /**
        @fn void VisiteurRecherche::visiter(CompteReel& _c) noexcept override;
        @brief Méthode qui permet de vérifier si un CompteReel est le compte recherché.
        @param _c : CompteReel& _c,CompteReel auquel le visiteur veut avoir accés pour le comparer au compte recherché.
    */
    void visiter(CompteReel& _c) noexcept override;

    /**
        @fn void VisiteurRecherche::visiter(CompteVirtuel& _c) noexcept override;
        @brief Méthode qui permet de rechercher un Compte parmis les fils du compte passé en paramètre et lui même.
        @param _c : CompteVirtuel& _c,CompteVirtuel auquel le visiteur veut avoir accés pour comparer ses fils et lui même au compte recherché.
    */
    void visiter(CompteVirtuel& _c) noexcept override;

    /**
        @fn CompteHierarchie* VisiteurRecherche::getResultat() const;
        @brief Méthode qui permet d'obtenir un pointeur sur le compte recherché s'il existe.
        @return Un pointeur sur le CompteHierarchie si le nom correspond à un  compte existant, nullptr sinon.
    */
    CompteHierarchie* getResultat() const {return resultat;}
private:
    /**
        @var int VisiteurRecherche::idcompte
        @brief Id du compte recherché.
    */
    int  idcompte;
    /**
      @var string VisiteurRecherche::nomcompte
       @brief Nom du compte recherché
     */
    std::string nomcompte;
    /**
        @var CompteHierarchie VisiteurRecherche::resultat
        @brief Pointeur sur le compte recherché lorsqu'il a été trouvé.
    */
    CompteHierarchie* resultat;

     /**
        @fn VisiteurRecherche::VisiteurRecherche() noexcept;
        @brief Constructeur privé
    */
    VisiteurRecherche(const int _id) noexcept : idcompte(_id), nomcompte(""), resultat(nullptr){}


    /**
       @fn VisiteurRecherche::VisiteurRecherche() noexcept;
       @brief Constructeur privé
   */
   VisiteurRecherche(const std::string & _nomcompte) noexcept : idcompte(-1), nomcompte(_nomcompte), resultat(nullptr){}

    /**
        @fn  VisiteurRecherche::VisiteurRecherche(const VisiteurRecherche& _v);
        @brief Constructeur par recopie privé
        @param _v : const VisiteurRecherche&, référence constante sur le VisiteurRecherche à recopier.
    */
    VisiteurRecherche (const VisiteurRecherche& _v) = default;

    /**
        @fn  VisiteurRecherche& VisiteurRecherche::operator=(const VisiteurRecherche& _v);
        @brief Suppression surcharge de l'opérateur d'affectation privé
        @param _v : const VisiteurRecherche&, référence constante sur le VisiteurRecherche à affecter.
    */
    VisiteurRecherche& operator=(const VisiteurRecherche& _v) = delete;

};



#endif // VISITEURRECHERCHE_H_INCLUDED
