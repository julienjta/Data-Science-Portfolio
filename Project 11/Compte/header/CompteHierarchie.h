#ifndef COMPTEHIERARCHIE_H_INCLUDED
#define COMPTEHIERARCHIE_H_INCLUDED

/**
    @file CompteHierarchie.h
    @brief CompteHierarchie est une classe mère pour les éléments de la hiérachie des comptes.
        Elle permet de manipuler tous les comptes via la même interface.
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 28 avril 2020
    @bug aucun détecté
    @warning COMPILE
*/

#include "../header/Recette.h"

/**
    @enum Type
    @brief représente les deux types de Compte : Virtuel (c'est-à-dire un compte qui n'est destiné qu'à regrouper des sous-comptes sans enregistrer aucune opération)
    et Réel (les comptes sur lesquels seront enregistrées les opérations.
*/
enum Type {
    //! @var VIRTUEL marque le compte comme étant de la classe CompteVirtuel
    VIRTUEL = 0,
    //! @var REEL marque le compte comme étant de la classe CompteReel
    REEL = 1
};


/**
    @class CompteHierarchie "CompteHierarchie.h"
    @brief CompteHierarchie est la classe mère pour les éléments de la hiérarchie des comptes qui permet de manipuler tous les comptes via la même interface.
*/

class CompteHierarchie{
    friend class HierarchieBuilder;
    friend class CompteManager;
    friend class VisiteurFree;

public :
    /**
        @fn virtual string CompteHierarchie::toString() const noexcept;
        @brief Méthode virtuelle qui retournera des informations sur les comptes.
        @return La première lettre du nom du poste du compte suivie du nom du compte.
    */
    virtual string toString() const noexcept;

    /**
        @fn virtual void CompteHierarchie::accepte(Visiteur& _v) noexcept;
        @brief Méthode pour les visiteurs.
        @param _v : Visiteur &, visiteur à accepter.
    */
    virtual void accepte(Visiteur& _v) noexcept = 0;

    /**
        @fn string CompteHierarchie::getNom() const noexcept;
        @brief Méthode qui permet d'obtenir le nom du compte.
        @return Le nom du compte.
    */
    string getNom() const noexcept {return nom;}

    /**
        @fn Poste CompteHierarchie::getPoste() const noexcept;
        @brief Methode qui retourne le poste d'un compte.
        @return RACINE ou DEPENSE ou RECETTE ou ACTIF ou PASSIF.
    */
    Poste getPoste() const noexcept { return poste->getPoste();}

    /**
        @fn Poste CompteHierarchie::getPosteCompte() const noexcept;
        @brief Methode qui retourne une réference const sur le PosteCompte d'un compte
        @return Une référence constante sur le PosteCompte du compte (Racine, Passif,Recette, Depense ou Actif)
    */
    const PosteCompte& getPosteCompte() const noexcept {return *poste;}

    /**
        @fn  virtual Type CompteHierarchie::getType() const noexcept;
        @brief Methode qui retourne le type d'un Compte.
        @return VIRTUEL si CompteVirtuel, REEL si CompteReel.
    */
    virtual Type getType() const noexcept = 0;

    /**
        @fn virtual const set<CompteHierarchie*> CompteHierarchie::getFils() const;
        @brief Methode qui permet d'obtenir les fils d'un compte.
        @return Ensemble des fils d'un compte.
        @exception FLSR_EXC_H : impossible de récupérer les fils d'un compte réel.
    */
    virtual const set<CompteHierarchie*> getFils() const = 0;


    /**
        @fn virtual void CompteHierarchie::ajouterFils(CompteHierarchie* _c);
        @brief Methode qui sera redéfinie. Elle permettra d'ajouter un fils à un CompteVirtuel.
        @param _c : CompteHierarchie*, pointeur sur le compte à ajouter
        @exception FLSR_EXC_H : impossible d'ajouter un fils à un compte réel.
    */
    virtual void ajouterFils(CompteHierarchie* _c) = 0;

    /**
        @fn virtual void CompteHierarchie::supprimerFils(CompteHierarchie* _c);
        @brief Methode qui sera redéfinie. Elle permettra de retirer un fils à un CompteVirtuel.
        @param _c : CompteHierarchie*, pointeur sur le compte à retirer
        @exception FLSR_EXC_H : impossible de retirer un fils à un compte réel.
    */
    virtual void supprimerFils(CompteHierarchie* _c) = 0;


    /**
        @fn virtual void CompteHierarchie::supprimerCompte();
        @brief Méthode virtuelle qui permet à l'utilisateur de supprimer le compte
        @exception SUPREL_EXC_C le compte a des transactions il ne peut être supprimé (pour un CompteReel)
        @exception SUPVIR_EXC_C les fils du compte n'ont pas été supprimés (pour un CompteVirtuel)
    */
    virtual void supprimerCompte() = 0;

    /**
        @fn  virtual void CompteHierarchie::undo(Originator* _o);
        @brief Méthode virtuelle qui permettra de restaurer un memento antérieur dans un compte réel.
        @param _o : Originator*, pointeur sur un originator qui va nous permettre de manipuler le memento.
        @exception MEMV_EXC_C : Tentative d'utiliser un memento sur un compte virtuel
    */
    virtual void undo(Originator* _o) = 0;

    /**
        @fn  virtual void CompteHierarchie::saveState(Originator* _o);
        @brief Méthode virtuelle qui permettra d'ajouter un memento à la liste de memento d'un compte reel.
        @param _o : Originator*, pointeur sur un originator qui va nous permettre de sauver le memento.
        @exception MEMV_EXC_C : Tentative d'utiliser un memento sur un compte virtuel
    */
    virtual void saveState(Originator _o) = 0;

    /**
        @fn int CompteHierarchie::getId() const noexcept;
        @brief Méthode qui permet de retourner l'identifiant d'un compte.
        @return l'identifiant du compte
    */
    int getId() const noexcept {return id;}

    /**
        @fn virtual Memento* CompteHierarchie::getDernierMemento();
        @brief Méthode virtuelle qui permettra de retourner de retourner le dernier Memento enregistré d'un CompteReel (le solde actuel)
        @exception MEMV_EXC_C : Tentative d'utiliser un memento sur un compte virtuel
        @return Une pointeur sur le dernier memento de la liste
    */
    virtual Memento* getDernierMemento() = 0;

    /**
        @fn virtual const list<Memento*> getMementos() const
        @brief Méthode virtuelle qui permettra de récupérer la liste de tous les Mementos
        @exception MEMV_EXC_C : Tentative d'utiliser un memento sur un compte virtuel
        @return Une liste non-modifiable de Mementos.
    */
     virtual const list<Memento*>& getMementos() const = 0;

protected:
    //methodes
    /**
        @fn CompteHierarchie::CompteHierarchie(const string& _nom);
        @brief Constructeur
        @param _nom : const string&, nom du compte à créer.
        @param _id : const int, identifiant du compte.
    */
    CompteHierarchie(const string& _nom, const int _id) noexcept : nom(_nom), id(_id) {}

    /**
        @fn CompteHierarchie::~CompteHierarchie();
        @brief Destructeur.
    */
    virtual ~CompteHierarchie(){}

    /**
        @var const PosteCompte* CompteHierarchie::poste
        @brief Pointeur sur un PosteCompte : Racine, Passif,Recette, Depense ou Actif.
    */
    const PosteCompte* poste;


private :
    //attributs
    /**
        @var string CompteHierarchie::nom
        @brief Le nom d'un Compte.
    */
    string nom;

    /**
        @var int CompteHierarchie::id
        @brief L'id d'un compte. Il est unique et est géré automatiquement par HierarchieBuilder.
    */
    int id;

    /**
        @fn  CompteHierarchie::CompteHierarchie (const CompteHierarchie& _c);
        @brief Supression constructeur par recopie privé.
        @param _c : const CompteHierarchie&: référence constante sur le compte à recopier.
    */
    CompteHierarchie (const CompteHierarchie& _c) =delete;

    /**
        @fn  CompteHierarchie& CompteHierarchie::operator=(const CompteHierarchie& _c);
        @brief Supression surcharge de l'opérateur d'affectation privé.
        @param _c : const CompteHierarchie : référence constante sur le compte à affecter.
    */
    CompteHierarchie& operator=(const CompteHierarchie& _c) = delete;
};
#endif // COMPTEHIERARCHIE_H_INCLUDED
