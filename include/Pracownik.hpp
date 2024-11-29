#ifndef PRACOWNIK_HPP
#define PRACOWNIK_HPP

#include <iomanip>
#include <iostream>
#include <memory>
#include <string>

// Stałe wynagrodzenia pracowników
const int WYNAGRODZENIE_INZ = 3000;
const int WYNAGRODZENIE_MAG = 2500;
const int WYNAGRODZENIE_MKT = 2800;
const int WYNAGRODZENIE_ROB = 2000;

class Pracownik
{
public:
    Pracownik(std::string imie);
    Pracownik();
    virtual ~Pracownik();

    Pracownik(const Pracownik& other);
    Pracownik& operator=(const Pracownik& other);

    Pracownik(Pracownik&& other) noexcept;
    Pracownik& operator=(Pracownik&& other) noexcept;

    virtual void print() const            = 0;
    virtual int  getWynagrodzenie() const = 0;

protected:
    std::string imie;
};

class Inz : public Pracownik
{
public:
    Inz(std::string imie, std::string wydzial);
    void print() const override;
    int  getWynagrodzenie() const override;

private:
    std::string wydzial;
};

class Mag : public Pracownik
{
public:
    Mag(std::string imie, bool obsl_widl);
    void print() const override;
    int  getWynagrodzenie() const override;

private:
    bool obsl_widl;
};

class Mkt : public Pracownik
{
public:
    Mkt(std::string imie, int follows);
    void print() const override;
    int  getWynagrodzenie() const override;

private:
    int follows;
};

class Rob : public Pracownik
{
public:
    Rob(std::string imie, double but);
    void print() const override;
    int  getWynagrodzenie() const override;

private:
    double but;
};

#endif // PRACOWNIK_HPP
