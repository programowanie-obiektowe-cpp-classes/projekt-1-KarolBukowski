#include "Pracownik.hpp"

// Implementacja klasy Pracownik
Pracownik::Pracownik(std::string imie) : imie(imie)
{}
Pracownik::Pracownik()  = default;
Pracownik::~Pracownik() = default;

Pracownik::Pracownik(const Pracownik& other)            = default;
Pracownik& Pracownik::operator=(const Pracownik& other) = default;

Pracownik::Pracownik(Pracownik&& other) noexcept            = default;
Pracownik& Pracownik::operator=(Pracownik&& other) noexcept = default;

// Implementacja klasy Inz
Inz::Inz(std::string imie, std::string wydzial) : Pracownik(imie), wydzial(wydzial)
{}
void Inz::print() const
{
    std::cout << "Inzynier: " << imie << ", Wydzial: " << wydzial << "\n";
}
int Inz::getWynagrodzenie() const
{
    return WYNAGRODZENIE_INZ;
}

// Implementacja klasy Mag
Mag::Mag(std::string imie, bool obsl_widl) : Pracownik(imie), obsl_widl(obsl_widl)
{}
void Mag::print() const
{
    std::cout << "Magazynier: " << imie << ", Obsluga wozka widlowego: " << (obsl_widl ? "tak" : "nie") << "\n";
}
int Mag::getWynagrodzenie() const
{
    return WYNAGRODZENIE_MAG;
}

// Implementacja klasy Mkt
Mkt::Mkt(std::string imie, int follows) : Pracownik(imie), follows(follows)
{}
void Mkt::print() const
{
    std::cout << "Marketer: " << imie << ", Liczba obserwujacych: " << follows << "\n";
}
int Mkt::getWynagrodzenie() const
{
    return WYNAGRODZENIE_MKT;
}

// Implementacja klasy Rob
Rob::Rob(std::string imie, double but) : Pracownik(imie), but(but)
{}
void Rob::print() const
{
    std::cout << "Robotnik: " << imie << ", Rozmiar buta: " << std::fixed << std::setprecision(1) << but << "\n";
}
int Rob::getWynagrodzenie() const
{
    return WYNAGRODZENIE_ROB;
}
