#ifndef FIRMA_HPP
#define FIRMA_HPP

#include "Kredyt.hpp"
#include "Pracownik.hpp"
#include <algorithm>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

// Stałe dla wydajności pracowników
const int CI   = 100;
const int CMag = 50;
const int CMkt = 80;
const int CR   = 120;

// Stałe dla kredytów
const int    MAX_KREDYT             = 36;
const double MAX_ZADLUZENIE_MNOZNIK = 3.0;

// Stałe do zwycięstwa
const int N_MIESIECY = 12;

class Firma
{
public:
    Firma();

    void   zatrudnij(std::unique_ptr< Pracownik > pracownik);
    void   wez_kredyt(double kwota, int czas_splaty);
    void   zaplac_wynagrodzenie();
    void   splac_raty();
    double oblicz_przychod();
    void   otrzymaj_przychod();
    double oblicz_zadluzenie() const;
    void   drukuj_pracownikow() const;
    void   drukuj_informacje() const;
    double get_stan_konta() const;
    double oblicz_wartosc_spolki() const;

private:
    double                                      stan_konta;
    int                                         n_prac;
    int                                         n_kredytow;
    int                                         n_mag;
    int                                         n_inz;
    int                                         n_mkt;
    int                                         n_rob;
    int                                         magazyn;
    std::vector< double >                       historia_przychodow;
    std::vector< std::unique_ptr< Pracownik > > pracownicy;
    std::vector< std::unique_ptr< Kredyt > >    kredyty;
};

#endif // FIRMA_HPP
