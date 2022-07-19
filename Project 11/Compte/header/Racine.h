#ifndef RACINE_H_INCLUDED
#define RACINE_H_INCLUDED

/**
    @file Racine.h
    @brief Racine permet de représenter le comportement d'un compte Racine, c'est-à-dire celui qui contient tous les autres comptes.
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/

#include "../header/PosteCompte.h"

/**
    @class Racine "Racine.h"
    @brief Racine permet de représenter le comportement d'un compte Racine, c'est-à-dire celui qui contient tous les autres comptes.
*/

class Racine: public PosteCompte{
public:
    /**
     @fn virtual Poste Racine::getPoste() const noexcept override;
     @brief  Redéfinition de la méthode virtuelle getPoste de PosteCompte. Cette méthode retourne le nom du poste Racine: RACINE.
     @return RACINE
    */
    Poste getPoste() const noexcept override {return RACINE;}
    /**
        @fn  virtual string Racine::getLetter() const noexcept override;
        @brief Redéfinition de la méthode virtuelle getLetter de PosteCompte. Cette méthode renvoie la première lettre d'un poste Racine : R.
        @return R
    */
    string getLetter() const noexcept override {return "R";}
    /**
        @fn static const PosteCompte& Racine::getInstance() noexcept;
        @brief Méthode qui permet d'obtenir l'instance Racine.
        @return instance
    */
    static const PosteCompte& getInstance() noexcept {return instance;}
    /**
        @fn virtual void Racine::debiter(double* _solde, double _montant) cont override;
        @brief Redéfinition de la méthode virtuelle getPoste de PosteCompte : lancement d'une exception, on ne peut pas débiter le compte racine.
        @exception ROOT_EXC_C Lancement d'ExceptionComptabilité : Impossible de débiter le compte racine.
    */
    void debiter(double *_solde, double _montant) const override;
    /**
        @fn virtual void Racine::crediter(double* _solde, double _montant) const override;
        @brief Redéfinition de la méthode virtuelle getPoste de PosteCompte : lancement d'une exception, on ne peut pas créditer le compte racine.
        @exception ROOT_EXC_C Lancement d'ExceptionComptabilité : Impossible de créditer le compte racine.
    */
    void crediter(double *_solde, double _montant) const override;
private:
     //attribut
    /**
        @var static Racine::Racine instance
        @brief instance Racine
    */
    //méthodes
    static Racine instance;
    /**
        @fn Racine::Racine();
        @brief Constructeur privé
    */
    Racine() = default;
    /**
        @fn Racine::~Racine();
        @brief Destructeur privé
    */
    ~Racine()=default;
    /**
        @fn  Racine::Racine(const Racine& _r);
        @brief Supression constructeur par recopie
    */
    Racine(const Racine& _r) = delete;

    /**
        @fn  Racine& Racince::operator=(const Racine& _r);
        @brief Supression de surcharge de l'opérateur d'affectation privé
    */
    Racine& operator=(const Racine& _r) = delete;
};




#endif // RACINE_H_INCLUDED
