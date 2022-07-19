#ifndef COMPTEVIRTUEL_H_INCLUDED
#define COMPTEVIRTUEL_H_INCLUDED

/**
    @file CompteVirtuel.h
    @brief CompteVirtuel permet de représenter les Comptes Virtuels (comptes destinés à regrouper des sous-compte sans enregistrer d'opérations).
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 29 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/

#include "../header/VisiteurRecherche.h"

/**
    @class CompteVirtuel "CompteVirtuel.h"
    @brief CompteVirutel représente les Compte Virtuels (comptes destinés à regrouper des sous-compte sans enregistrer d'opération).
*/
class CompteVirtuel: public CompteHierarchie{
    friend class HierarchieBuilder;
    friend class CompteManager;
    friend class VisiteurFree;

public :
    /**
        @fn  Type CompteVirtuel::getType() const noexcept override;
        @brief Redéfinition de la méthode getType de CompteHierarchie afin qu'elle retourne le type d'un compte virtuel.
        @return VIRTUEL
    */
    Type getType() const noexcept override {return VIRTUEL;}

    /**
        @fn void CompteVirtuel::accepte(Visiteur& _v) noexcept override;
        @brief Redéfinition de la méthode accepte(Visiteur& _v) de CompteHierarchie.
        @param _v : Visiteur &, visiteur à accepter.
    */
    void accepte(Visiteur& _v) noexcept override;

    /**
        @fn const set<CompteHierarchie*> CompteVirtuel::getFils() const override;
        @brief Methode qui permet d'obtenir les fils du compte.
        @return Ensemble des fils du compte.
    */
    const set<CompteHierarchie*> getFils() const override {return fils;}

    /**
        @fn void CompteVirtuel::ajouterFils(CompteHierarchie* _c) noexcept override;
        @brief Redéfinition de ajouterFils(CompteHierarchie* _c) de CompteHierarchie. Cette méthode permet d'ajouter un fils d'un CompteVirtuel.
        @param _c : CompteHierarchie*, pointeur sur le compte à ajouter.
    */
    void ajouterFils(CompteHierarchie* _c) noexcept override { fils.insert(_c);}

    /**
        @fn void CompteHierarchie::supprimerFils(CompteHierarchie* _c)noexcept override;
        @brief Redéfinition de supprimerFils. Elle permettra de retirer un fils à un CompteVirtuel.
        @param _c : CompteHierarchie*, pointeur sur le compte à retirer.
    */
    void supprimerFils(CompteHierarchie* _c) noexcept override { fils.erase(_c);}

    /**
        @fn void CompteVirtuel::supprimerCompte()override;
        @brief Redéfinition de supprimerCompte() de CompteHierarchie.
        @exception SUPVIR_EXC_C les fils du compte n'ont pas été supprimés.
    */
    void supprimerCompte() override;

    /**
        @fn  void CompteVirtuel::undo(Originator* _o) override;
        @brief Méthode virtuelle undo redéfinie de CompteHierarchie. On ne peut pas utiliser cette méthode avec un compte virtuel : lancement d'une exception.
        @exception MEMV_EXC_C : Tentative d'utiliser un memento sur un compte virtuel.
    */
    void undo(Originator* _o) override;

    /**
        @fn  void CompteHierarchie::saveState(Originator* _o) override;
        @brief Méthode virtuel de saveState de CompteHierarchie redéfinie. On ne peut pas utiliser cette méthode avec un compte virtuel : lancement d'une exception.
        @exception MEMV_EXC_C : Tentative d'utiliser un memento sur un compte virtuel
    */
    void saveState(Originator _o) override;

    /**
        @fn Memento* CompteVirtuel::getDernierMemento()override;
        @brief Genère une exception car ne peut être lancé que pour un compte reel.
        @exception MEMV_EXC_C : Tentative d'utiliser un memento sur un compte virtuel.
    */
    Memento* getDernierMemento() override;

    /**
        @fn const list<Memento*>& getMementos() const override;
        @brief Génère une exception car ne peut être lancé que pour un compte réel.
        @exception MEMV_EXC_C : Tentative d'utiliser un memento sur un compte virtuel.
    */
    const list<Memento*>& getMementos() const override;


private :
    /**
        @fn CompteVirtuel::CompteVirtuel(const string& _nom) noexcept;
        @brief Constructeur privé
        @param _nom : const string&, nom du compte virtuel à créer.
    */
    CompteVirtuel(const string& _nom, int _id) noexcept : CompteHierarchie(_nom,_id) {}

    /**
        @fn CompteVirtuel::~CompteVirtuel() noexecpt;
        @brief Destructeur privé
    */
    ~CompteVirtuel() noexcept = default;

    /**
        @fn  CompteVirtuel::CompteVirtuel (const CompteVirtuel& _c);
        @brief Supression constructeur par recopie privé
        @param _c : const CompteVirtuel&: référence constante sur le compte virtuel à recopier.
    */
    CompteVirtuel(const CompteVirtuel& _c) = delete;


     /**
        @fn  CompteVirtuel& CompteVirtuel::operator=(const CompteVirtuel& _c);
        @brief Supression de surcharge de l'opérateur d'affectation privé
        @param _c : const CompteVirtuel & : référence constante sur le compte virtuel à affecter.
    */
    CompteVirtuel& operator=(const CompteVirtuel& _c) = delete;

    //attributs
    /**
        @var set<CompteHierarchie*> CompteHierarchie::fils
        @brief L'ensemble des fils d'un compte virtuel.
    */
    set<CompteHierarchie*> fils;


};



#endif // COMPTEVIRTUEL_H_INCLUDED
