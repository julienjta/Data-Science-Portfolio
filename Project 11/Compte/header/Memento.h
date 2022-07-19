#ifndef MEMENTO_H_INCLUDED
#define MEMENTO_H_INCLUDED

/**
    @file Memento.h
    @brief Le Memento permet de sauvegarder la date et le solde des rapprochements + solde actuel.
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note
*/

#include "../../Transaction/header/exceptiontransaction.h"

/**
    @class Memento "Memento.h"
    @brief Le Memento permet de sauvegarder la date et le solde du dernier rapprochement.
*/
class Memento{
public :
    /**
        @fn Memento::Memento(const double _solde, const time_t _date);
        @brief Constructeur
    */
    Memento(const double _solde, const time_t _date = time(nullptr)) noexcept;
    /**
        @fn double Memento::getSolde()const noexcept;
        @brief Méthode qui retourne le solde du memento.
        @return Un double qui représente le solde enregistré.
    */
    double getSolde() const noexcept {return solde;}
    /**
        @fn time_t Memento::getDate() const noexcept;
        @brief Méthode qui permet d'obtenir la date du memento.
        @return La date où a été enregistré le solde dans le memento.
    */
    time_t getDate() const noexcept {return date;}

private:
    /**
        @fn time_t Memento::date;
        @brief Correspond à la date où l'on enregistre le solde dans le memento.
    */
    time_t date;

    /**
        @fn int Memento::solde;
        @brief Solde du memento.
    */
    double solde;

};
#endif // MEMENTO_H_INCLUDED
