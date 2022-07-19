/**
    @file Memento.cpp
    @brief Définition des fonctions membres de la classe Memento.
    @author Ophélie Delattre / Simon Lepage
    @version v3
    @date 30 avril 2020
    @bug aucun détecté
    @warning COMPILE
    @note Aucune
*/

#include "../header/Memento.h"

Memento::Memento(const double _solde, const time_t _date) noexcept
{
    solde = _solde;
    date = _date; // date est à time(nullptr) par défaut, cf le header
}
