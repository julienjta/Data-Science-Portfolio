#ifndef COMPTEMANAGER_H_INCLUDED
#define COMPTEMANAGER_H_INCLUDED

/**
    @file CompteManager.h
    @brief CompteManager est un singleton qui permet de gérer l'ensemble des compte.
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 29 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/

#include "../../Transaction/header/transactionmanager.h"

/**
    @class CompteManager "CompteManager.h"
    @brief CompteManager gère l'ensemble des Comptes.
*/
class CompteManager{
public:
    /**
        @fn static CompteManager& CompteManager::getInstance() noexcept;
        @brief Méthode qui permet d'obtenir l'instance CompteManager.
        @return instance du singleton
    */
    static CompteManager& getInstance() noexcept {return instance;}
    /**
        @var static int CompteManager::init
        @brief Attribut qui permet de gérer automatiquement les initialisation des comptes
    */
    static int init;

    /**
        @fn CompteHierarchie* CompteManager::getCompte(int _id)const;
        @brief Méthode qui permet de renvoyer un pointeur sur un objet CompteHierarchie dont l'id a été passé en paramêtre.
        @param _id : int id du compte sur lequel on veut obtenir un pointeur.
        @return Un pointeur sur le compte recherché s'il existe, nullptr sinon.
        @exception IDNF_EXC_H : l'ID recherché n'existe pas.
    */
    CompteHierarchie* getCompte(int _id)const;

    /**
        @fn CompteHierarchie* getPere(const CompteHierarchie* _c)const noexcept;
        @brief Retrouve le père d'un compte passé en argument.
        @param _c : const CompteHierarchie* pointeur sur le fils à trouver.
        @return Un pointeur sur le compte père s'il existe, sinon nullptr.
    */
    CompteHierarchie* getPere(CompteHierarchie* _c) const noexcept;

    /**
        @fn void CompteManager::affiche()const noexcept;
        @brief Méthode qui permet d'afficher la hiérarchie des comptes
        @param _arbre : QTreeWidget* const, l'arbre dans lequel ajouter les comptes
        @param _devise : QString const&, la devise dans laquelle afficher les soldes
    */
    void affiche(QTreeWidget* const _arbre, QString const& _devise) const noexcept;


    /**
     * @fn list<CompteHierarchie*> getListeComptePoste(Poste_p) const;
     * @brief Méthode qui permet d'obtenir la liste de Compte qui on pour poste le poste passé en paramètre.
     * @param _p : Poste, Poste pour lequel la liste de Compte.
     * @return La liste de Compte qui on pour poste le poste passé en paramètre.
     */

    list<CompteHierarchie*> getListeComptePoste(Poste _p)const;

    /**
     * @fn void getListeComptes(QStringList* _liste_compte,list<int>* _liste_id,int const _seul_compte_reel)const noexcept;
     * @brief Méyhode qui permet d'obtenir deux listes : la liste des id des comptes d'un certains type (reel,virtuel, tous) et la liste des noms des comptes avec la première l'être de leur poste associés aux id
     * @param _liste_compte : QStringList*, liste des comptes contenant la première lettre du poste du compte et le nom du compte qui sera remplie par la méthode.
     * @param _liste_id : liste<int>*, liste des id des comptes qui sera rempli par la méthode.
     * @param _seul_compte_reel : int const, type du compte pour lesquels ont veut obtenir ces deux listes : 0 pour les compte virtuels, 1 pour les comptes réels, un autre entier pour tous les comptes.
     */

    void getListeComptes(QStringList* _liste_compte,list<int>* _liste_id,int const _seul_compte_reel)const noexcept;

    /**
        @fn  void CompteManager::ajouterFils(int  _id_pere, const string& _nom_fils, Type _t, Poste _p);
        @brief Méthode qui permet d'ajouter un fils à un CompteVirtuel.
        @param _id_pere : int, id du CompteVirtuel auquel on veut ajouter un fils.
        @param _nom_fils : const string&, nom du compte fils que l'on veut ajouter.
        @param _t : const string&, type du compte fils que l'on veut ajouter : VIRTUEL ou REEL.
        @param _p : Poste, poste du compte fils que l'on veut ajouter (DEPENSE, RECETTE, ACTIF, PASSIF).
        @exception TYPE_EXC_H Type de compte inconnu.
        @exception POSTE_EXC_H Type de poste inconnu.
        @exception RULE_EXC_H Impossible d'ajouter ce compte fils à ce compte.
    */
    void ajouterFils(int _id_pere, const string& _nom_fils, Type _t, Poste _p);

    /**
        @fn void supprimerCompte(int _id);
        @brief Méthode qui permet de supprimer un Compte.
        @param _id : int, id du compte que l'on veut supprimer.
        @exception IDNF_EXC_H l'ID recherché n'existe pas.
        @exception SUPREL_EXC_C le compte a des transactions il ne peut être supprimé.
        @exception SUPVIR_EXC_C les fils du compte n'ont pas été supprimés.
        @exception RULE_EXC_H le compte est nécessaire au fonctionnement de l'application et ne peut être supprimé.
    */
    void supprimerCompte(int _id);

    /**
        @fn void CompteManager::deplacerFils(int _id_fils, int _id_futur_pere);
        @brief Methode qui permet de changer de place un compte dans la hiérarchie des comptes.
        @param _id_futur_pere : int, id du compte sous lequel on veut déplacer le compte (c'est à dire le nouveau père du compte).
        @param _id_fils : int, id du compte à déplacer.
        @exception IDNF_EXC_H l'ID recherché n'existe pas.
        @exception RULE_EXC_H si le futur père n'est pas du bon type.
        @exception FLSR_EXC_H si le futur père est réel.
        @exception FLSR_EXC_H impossible de retirer un fils à un compte réel
        @exception FLSR_EXC_H impossible d'ajouter un fils à un compte réel
        @exception DSELF_EXC_H impossible de déplacer un compte sous lui-même.
        @exception DSON_EXC_H impossible de déplacer un compte sous un de ses fils.
    */
    void deplacerFils(int _id_fils, int _id_futur_pere);

    /**
        @fn void CompteManager::charger() const;
        @brief Méthode qui permet de charger un fichier comptenant des comptes enregistrés lors des sessions précédente. Si la hiérarchie actuelle n'est pas vide, elle est sauvée dans le fichier path du CompteManager avant que le fichier _file soit chargé.
        @param _file : const string&, le chemin du fichier à charger.
        @exception UFND_EXC_F impossible d'ouvrir le fichier.
        @exception SNTX_EXC_F le fichier est mal formé.
    */
    void charger(const string& _file);

    /**
        @fn void CompteManager::setPath(const string& _file) const noexcept;
        @brief Méthode qui permet de modifier l'attribut du path afin de renseigner un nouveau chemin d'un fichier où enregistrer les comptes ou à partir duquel sont restaurés les comptes enregistrés lors des sessions précédentes.
        @param _file : const string&, nouveau chemin du fichier.
    */
    void setPath(const string& _file) noexcept;

    /**
        @fn string const& CompteManager::getPath() const noexcept;
        @brief retourne le chemin du fichier de sauvegarde utilisé
        @return le chemin du fichier.
    */
    string const& getPath() const noexcept;

    /**
        @fn bool CompteManager::isDefaultPath() const noexcept;
        @brief vérifie si aucune sauvegarde n'a eu lieu.
        @return true si aucune sauvegarde n'a eu lieu, false sinon.
    */
    bool isDefaultPath() const noexcept;

    /**
        @fn void CompteManager::sauver();
        @brief Méthode qui permet de sauver les comptes dans le fichier de chemin path.
        @param _file : const string&, le chemin du fichier dans lequel sauvegarder.
        @exception UFND_EXC_F impossible d'ouvrir le fichier.
    */
    void sauver(const string& _file = "");
    /**
        @fn void CompteManager::cloturer(CompteHierarchie* resultat);
        @brief Méthode permettant de clôturer le livre : c'est à dire remettre à zéro les comptes de recette et de dépense par l'intermédiaire d'un compte Résultat.
        @param _resultat : CompteHierarchie*, compteHierarchie (reel et passif) à utiliser pour réaliser la cloture.
    */
    void cloturer(CompteHierarchie* _resultat);

    /**
     * @fn CompteHierarchie* CompteManager::gestionCompteResultat();
     * @brief Cette méthode permet de gérer le choix du compte de cloture (si bool=false) ou la création d'un compte pour la cloture (si bool= true)
     * @param _nouveau : bool, vaut true si on veut créer un nouveau compte de cloture, false si on choisi un compte de cloture parmis les passifs existant
     * @param _id : int, _id représent l'id du père du nouveau compte de cloture si on souhaite en créer un nouveau (bool = true) et l'id du compte de cloture si on en a choisi un déjà existant
     * @param _nom : QString, _nom représent le nom du nouveau compte de cloture si l'on souhaire en créé un nouveau
     * @return Un pointeur sur le compte de cloture créé ou le compte de cloture choisi, s'il a été crée ou existe, nullptr sinon.
    */
    CompteHierarchie* gestionCompteResultat(bool _nouveau, int _id, QString _nom="");

    /**
        @fn void CompteManager::rapprocherCompte(int _id);
        @brief Méthode qui permet le rapprochement d'un compte : c'est-à-dire figer des transactions passées d'un compte.
        @param _id : int, id du compte sur lequel on veut faire le rapprochement.
        @exception MEMV_EXC_C : Tentative d'utiliser un memento sur un compte virtuel
        @exception IDNF_EXC_H : l'ID recherché n'existe pas.
    */
    void rapprocherCompte(int _id);
    /**
     * @fn CompteHierarchie* CompteManager::gestionCapitauxPropre();
     * @brief Cette méthode permet de gérer le choix du compte du capitaux propre (si bool=false) ou le création d'un compte capitaux propre (si bool= true)
     * @param _nouveau : bool, vaut true si on veut créer un nouveau compte de capitaux propre, false si on choisi un compte de capitaux propre parmis les passifs existant
     * @param _id : int, _id représent l'id du père du nouveau compte du capitaux propre si on souhaite en créer un nouveau (bool = true) et l'id du compte de capitaux propre si on en a choisi un déjà existant
     * @param _nom : QString, _nom représent le nom du nouveau compte de capitaux propre si l'on souhaire en créé un nouveau
     * @return Un pointeur sur le compte de capitaux propre créé ou le compte de capitaux propre choisi, s'il a été crée ou existe, nullptr sinon.
    */
    CompteHierarchie* gestionCapitauxPropre(bool _nouveau, int _id, QString _nom="");

    /**
        @fn int CompteManager::getSolde(int _id)const;
        @brief Méthode qui permet d'obtenir le solde d'un compte.
        @param _id : int id du compte pour lequel on veut obtenir le solde.
        @exception IDNF_EXC_H : l'ID recherché n'existe pas.
        @return Le solde du compte dont l'id a été passé en paramètre si le compte existe.
    */
    double getSolde(int _id);

    /**
        @fn void CompteManager::crediterCompte(int _id, double _montant).
        @brief Methode qui permet de créditer un compte Reel.
        @param _id : int, id du compte à créditer.
        @param _montant : double, montant à créditer sur le compte.
        @exception IDNF_EXC_H : l'ID recherché n'existe pas.
        @exception MEMV_EXC_C : Tentative d'utiliser un memento sur un compte virtuel
        @exception ROOT_EXC_C Lancement d'ExceptionComptabilité : Impossible de crediter le compte racine.
    */
    void crediterCompte(int _id, double _montant);
    /**
        @fn void CompteManager::debiterCompte(int _id, double _montant).
        @brief Methode qui permet de debiter un compte Reel.
        @param _id : int, id du compte à débiter.
        @param _montant : double, montant à débiter sur le compte.
        @exception IDNF_EXC_H : l'ID recherché n'existe pas.
        @exception MEMV_EXC_C : Tentative d'utiliser un memento sur un compte virtuel
        @exception ROOT_EXC_C Lancement d'ExceptionComptabilité : Impossible de débiter le compte racine.
    */
    void debiterCompte(int _id, double _montant);

    /**
        @fn Originator* CompteMananger::getOriginator() noexcept;
        @brief Méthode qui permet de retourner l'Origininator.
        @return Un pointeur sur l'origniator
    */
    Originator* getOriginator() noexcept {return o;}
private :
    //methode
    /**
        @fn CompteManager::CompteManager() noexcept;
        @brief Constructeur privé
    */
    CompteManager() noexcept;

    /**
        @fn CompteManager::~CompteManager();
        @brief Destructeur privé
    */
    ~CompteManager();

    /**
        @fn  CompteManager::CompteManager (const CompteManager& _c);
        @brief Constructeur par recopie, privé
        @param _c : const CompteManager &: référence constante sur le CompteManager à recopier.
    */
    CompteManager(const CompteManager& _c) = default;


     /**
        @fn  CompteManager& CompteManager::operator=(const CompteManager& _c);
        @brief Surcharge de l'opérateur d'affectation, privé.
        @param _c : const CompteManager & : référence constante sur le CompteManager à affecter.
    */
    CompteManager& operator=(const CompteManager& _c) = default;

    //attribut
    /**
        @var static CompteManager::CompteManager instance
        @brief instance CompteManager.
    */
    static CompteManager instance;

    /**
        @var CompteHierarchie* CompteManager::racine
        @brief Pointeur sur le Compte Racine : le compte qui contient tous les autres comptes.
    */
    CompteHierarchie* racine;

    /**
        @var string CompteMananger::path
        @brief Chemin du fichier où sauver les informations sur les comptes.
    */
    string path;

    /**
        @var Originator * CompteManagor::o
        @brief Originator qui permet de gérer les mementos des CompteReel.
    */
    Originator *o;


    /**
        @var int CompteManager::nb_cloture
        @brief Attribut qui permet de gérer automatiquement les references des clotures.
    */
    int nb_cloture;

};



#endif // COMPTEMANAGER_H_INCLUDED
