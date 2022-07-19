#ifndef COMPTEREEL_H_INCLUDED
#define COMPTEREEL_H_INCLUDED

/**
    @file CompteReel.h
    @brief CompteReel permet de représenter les compte réels (les comptes sur lesquels auront lieu les opérations).
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 29 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/

#include "../header/CompteVirtuel.h"

#include <iostream>
#include <list>
#include <ctime>

/**
    @class CompteReel "CompteReel.h"
    @brief CompteReel représente les compte réels (les comptes sur lequels auront lieu les opérations).
*/
class CompteReel: public CompteHierarchie{
    friend class HierarchieBuilder;
    friend class CompteManager;
    friend class VisiteurFree;

public :
    /**
        @fn  Type CompteReel::getType() const noexcept override;
        @brief Redéfinition de la méthode getType de CompteHierarchie afin qu'elle retourne le type d'un compte réel.
        @return REEL
    */
    Type getType() const noexcept override {return REEL;}

    /**
        @fn void CompteReel::accepte(Visiteur& _v)noexcept override;
        @brief Redéfinition de la méthode accepte(Visiteur& _v) de CompteHierarchie.
        @param _v : Visiteur &, visiteur à accepter
    */
    void accepte(Visiteur& _v) noexcept override;

    /**
        @fn    const set<CompteHierarchie*> CompteReel::getFils() const override;
        @brief Methode redéfinie. Ne fait rien sur CompteReel car il n'a pas de fils.
        @return Ensemble des fils du compte.
        @exception FLSR_EXC_H : impossible de récupérer les fils d'un compte réel.
    */
    const set<CompteHierarchie*> getFils() const override;

    /**
        @fn void CompteReel::ajouterFils(CompteHierarchie* _c) override;
        @brief Redéfinition de ajouterFils(CompteHierarchie* _c) de CompteHierarchie. Cette méthode ne fait rien sur CompteReel car il n'a pas de fils.
        @exception FLSR_EXC_H : impossible d'ajouter un fils à un compte réel.
    */
    void ajouterFils(CompteHierarchie* _c) override;

    /**
        @fn virtual void CompteHierarchie::supprimerFils(CompteHierarchie* _c);
        @brief Methode qui sera redéfinie. Ne fait rien sur CompteReel car il n'a pas de fils.
        @exception FLSR_EXC_H : impossible de retirer un fils à un compte réel.
    */
    void supprimerFils(CompteHierarchie* _c) override;

    /**
        @fn void CompteReel::supprimerCompte() override;
        @brief Redéfinition de supprimerCompte de CompteHierarchie. Permet de supprimer un compte si il n'a pas de transactions.
        @exception SUPREL_EXC_C le compte a des transactions il ne peut pas être supprimé.
    */
    void supprimerCompte() override;

    /**
        @fn  void CompteReel::undo(Originator* _o) noexcept override;
        @brief Méthode qui permet de restaurer un memento antérieur.
        @param _o : Originator*, pointeur sur un originator qui va nous permettre de manipuler le memento.
    */
    void undo(Originator* _o) noexcept override;

    /**
        @fn  void CompteReel::saveState(Originator* _o) noexcept override;
        @brief Méthode qui permet d'ajouter un memento à la liste de memento.
        @param _o : Originator*, pointeur sur un originator qui va nous permettre de sauver le memento.
    */
    void saveState(Originator _o) noexcept override{ mementos.push_back(_o.saveState());}


    /**
        @fn Memento* CompteReel::getDernierMemento noexcept override();
        @brief Méthode qui permet de retourner de retourner le dernier Memento enregistré (le solde actuel)
        @return Une pointeur sur le dernier memento de la liste
    */
     Memento* getDernierMemento() noexcept override {return mementos.back();}

    /**
        @fn const list<Memento*>& getMementos() const noexcept override;
        @brief Méthode qui permet de récupérer la liste de tous les Mementos
        @return Une liste non-modifiable de Mementos.
    */
    const list<Memento*>& getMementos() const noexcept override {return mementos;}

private:
    //méthode
    /**
        @fn CompteReel::CompteReel(const string& _nom);
        @brief Constructeur privé.
        @param _nom : const string&, nom du compte réel à créer.
    */
    CompteReel(const string& _nom,int _id) noexcept : CompteHierarchie(_nom,_id) {}

    /**
        @fn CompteReel::~CompteReel() noexcept;
        @brief Destructeur privé
    */
    ~CompteReel() noexcept override;

    /**
        @fn  CompteReel::CompteReel (const CompteReel& _c);
        @brief Suppresion constructeur par recopie
        @param _c : const CompteReel&: référence constante sur le compte réel à recopier.
    */
    CompteReel(const CompteReel& _c)=delete;

     /**
        @fn  CompteReel& CompteReel::operator=(const CompteReel& _c);
        @brief Suprresion de surcharge de l'opérateur d'affectation privé.
        @param _c : const CompteReel & : référence constante sur le compte réel à affecter.
    */
    CompteReel& operator=(const CompteReel& _c)=delete;


    //attributs
    /**
        @var liste<Memento*> CompteReel::mementos
        @brief Liste de mementos qui permet de garder en mémoire les soldes des derniers rapprochements.
    */
    list<Memento*> mementos;

};


#endif // COMPTEREEL_H_INCLUDED
