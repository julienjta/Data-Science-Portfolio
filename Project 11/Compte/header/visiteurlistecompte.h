#ifndef VISITEURLISTECOMPTE_H
#define VISITEURLISTECOMPTE_H

/**
    @file visiteurlistecompte.h
    @brief VisiteurListeCompte est un visiteur qui permet de recueillir la liste des comptes.
    @author Jérémy Godde d'après un modèle de Simon Lepage
    @version v1
    @date 23 mai 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/

#include "../header/VisiteurGetSolde.h"

/**
    @class VisiteurListeCompte "visiteurlistecompte.h"
    @brief VisiteurListeCompte est un visiteur qui permet de recueillir la liste des comptes.
*/

class VisiteurListeCompte : public Visiteur{
    friend CompteManager;
public:
    /**
        @fn void VisiteurListeCompte::visiter(CompteReel& _c) noexcept;
        @brief Méthode qui permet de parcourir un CompteReel
        @param _c : CompteReel&, CompteReel auquel le visiteur veut avoir accés pour recueillir son nom.
    */
    void visiter(CompteReel& _c) noexcept;
    /**
        @fn void VisiteurListeCompte::visiter(CompteVirtuel& _c) noexcept;
        @brief Méthode qui permet de parcourir un CompteVirtuel
        @param _c : CompteVirtuel&, CompteVirtuel auquel le visiteur veut avoir accés pour recueillir son nom.
    */
    void visiter(CompteVirtuel& _c) noexcept;

private:
    /**
        @fn void VisiteurListeCompte::fillItem(CompteHierarchie& _c, QTreeWidgetItem* _item) noexcept{
        @brief Méthode qui permet de remplir un QTreeWidgetItem* avec les informations d'un compte.
        @param _c : CompteHierarchie* ,compte dont on veut recueillir son nom.
    */
    void fillListe(CompteHierarchie& _c) noexcept;

     /**
        @fn VisiteurListeCompte::VisiteurListeCompte();
        @brief Constructeur privé
        @param _liste : QStringList*,la liste dans laquelle ajouter les comptes
        @param _liste_id : std::list<int>*,la liste dans laquelle ajouter les id
        @param _seul_reel : int, si 0, seulement les virtuels, si 1, seulement les réels, sinon tous
    */
    VisiteurListeCompte(QStringList* _liste,list<int>* _liste_id, int _seul_reel = 1) : liste(_liste),liste_id(_liste_id),seul_reel(_seul_reel) {}

    /**
        @fn  VisiteurListeCompte::VisiteurListeCompte(const VisiteurListeCompte& _v);
        @brief Constructeur par recopie privé.
        @param _v : const VisiteurListeCompte&, référence constante sur le VisiteurListeCompte à recopier.
    */
    VisiteurListeCompte (const VisiteurListeCompte& _v) = default;

    /**
        @fn  VisiteurListeCompte& VisiteurListeCompte::operator=(const VisiteurListeCompte& _v);
        @brief Supression Surcharge de l'opérateur d'affectation privé.
        @param _v : const VisiteurListeCompte&, référence constante sur le VisiteurListeCompte à affecter.
    */
    VisiteurListeCompte& operator=(const VisiteurListeCompte& _v) = delete;

    /**
       @fn VisiteurListeCompte::~VisiteurListeCompte();
       @brief Destructeur privé
   */
    ~VisiteurListeCompte() = default;

    //attributs
    /**
        @var QStringList* VisiteurListeCompte::liste
        @brief Liste des comptes de la hierarchie
    */
    QStringList* liste;
    /**
        @var list<int>* VisiteurListeCompte::liste_id
        @brief Liste des ids comptes de la hierarchie
    */
    list<int>* liste_id;
    /**
     * @var int VisiteurListeCompte::seul_reel
     * @brief Repésente le type des comptes de la hierarchie auquel on s'interresse 0, seulement les virtuels, si 1, seulement les réels, sinon tous
    */
    int seul_reel;
};

#endif // VISITEURLISTECOMPTE_H
