#ifndef GRA_HPP
#define GRA_HPP

#include "Firma.hpp"
#include <iostream>
#include <memory>
#include <string>

const double WARTOSC_DO_ZWYCIESTWA = 100000.0;

class Gra
{
public:
    Gra();

    void akcja_gracza();
    bool get_stan() const;
    void tick();

private:
    std::unique_ptr< Firma > firma;
    bool                     stan;
};

#endif // GRA_HPP
