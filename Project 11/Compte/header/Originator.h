#ifndef ORIGINATOR_H_INCLUDED
#define ORIGINATOR_H_INCLUDED

/**
    @file Originator.h
    @brief Originator permet de manipuler les mementos
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note
*/

#include "../header/Memento.h"

/**
    @class Originator "Originator.h"
    @brief Originator permet de manipuler les mementos.
*/
class Originator{
public:
    /**
        @fn Originator::Originator();
        @brief Constructeur
    */
    Originator() = default;

    /**
        @fn void Originator::setSolde(const double _solde, const time_t _date = time(nullptr)) noexcept;
        @brief Méthode qui permet de modifier le solde.
        @param _solde : const double, nouveau solde.
        @param _date : const time_t, date du nouveau solde.
    */
    void setSolde(const double _solde, const time_t _date = time(nullptr)) noexcept{
        solde = _solde;
        date = _date;
    }

    /**
        @fn int Originator::getSolde()const noexcept;
        @brief Méthode qui retourne le solde.
        @return Un double qui représente le solde.
    */
    double getSolde() const noexcept {return this->solde;}

    /**
        @fn const time_t& Originator::getDate()const noexcept;
        @brief Méthode qui retourne le data où le solde a été enregistré.
        @return Date d'enregistrement du solde.
    */
    const time_t& getDate() const noexcept {return this->date;}

    /**
        @fn Memento* Originator::saveState() noexcept;
        @brief Méthode qui permet d'enregistre le solde dans une nouveau Memento.
        @return Un pointeur sur le Memento créé.
    */
    Memento* saveState() noexcept {return new Memento(solde,date);}

    /**
        @fn void Originator::restaureMemento(Memento _memento) noexcept;
        @brief Methode qui permet de restaurer un memento précedemment enregistré.
        @param _memento : Memento, Memento que l'on veut restaurer.
    */
    void restoreMemento(Memento _memento) noexcept {solde = _memento.getSolde();date = _memento.getDate();}
private:
     /**
        @fn time_t Originator::date;
        @brief Correspond à la date où l'on enregistre ou modifie le solde.
    */
    time_t date;

    /**
        @fn double Originator::solde;
        @brief Solde
    */
    double solde;
};

#endif // ORIGINATOR_H_INCLUDED
