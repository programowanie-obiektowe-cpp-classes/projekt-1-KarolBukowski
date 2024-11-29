#include "Firma.hpp"

Firma::Firma() : stan_konta(10000), n_prac(0), n_kredytow(0), n_mag(0), n_inz(0), n_mkt(0), n_rob(0), magazyn(0)
{
    // Zatrudnij pracowników na początku gry
    zatrudnij(std::make_unique< Inz >("Karol Bukowski", "MEiL"));
    zatrudnij(std::make_unique< Mag >("Karol Bukowski", true));
    zatrudnij(std::make_unique< Mkt >("Karol Bukowski", 123));
    zatrudnij(std::make_unique< Rob >("Karol Bukowski", 41.5));
}

void Firma::zatrudnij(std::unique_ptr< Pracownik > pracownik)
{
    if (dynamic_cast< Inz* >(pracownik.get()))
    {
        n_inz++;
    }
    else if (dynamic_cast< Mag* >(pracownik.get()))
    {
        n_mag++;
    }
    else if (dynamic_cast< Mkt* >(pracownik.get()))
    {
        n_mkt++;
    }
    else if (dynamic_cast< Rob* >(pracownik.get()))
    {
        n_rob++;
    }
    pracownicy.push_back(std::move(pracownik));
    n_prac++;
}

void Firma::wez_kredyt(double kwota, int czas_splaty)
{
    if (czas_splaty > MAX_KREDYT)
    {
        std::cout << "Zbyt dlugi okres splaty. Maksymalny okres: " << MAX_KREDYT << " miesiecy.\n";
        return;
    }

    double oprocentowanie = 0.05 + 0.05 * (czas_splaty / 12);
    kredyty.push_back(std::make_unique< Kredyt >(kwota, czas_splaty, oprocentowanie));
    n_kredytow++;
    stan_konta += kwota;
}

void Firma::zaplac_wynagrodzenie()
{
    int wynagrodzenie = 0;
    for (const auto& pracownik : pracownicy)
    {
        wynagrodzenie += pracownik->getWynagrodzenie();
    }
    stan_konta -= wynagrodzenie;
}

void Firma::splac_raty()
{
    for (auto it = kredyty.begin(); it != kredyty.end();)
    {
        double rata = (*it)->splac_rate();
        stan_konta -= rata;
        if ((*it)->czy_splacony())
        {
            it = kredyty.erase(it);
            n_kredytow--;
        }
        else
        {
            ++it;
        }
    }
}

double Firma::oblicz_przychod()
{
    int pojemnosc_magazynu = n_mag * CMag;
    int cena_produktu      = n_inz * CI;
    int popyt              = n_mkt * CMkt;

    int teoretyczna_produkcja = n_rob * CR;

    int faktyczna_produkcja = std::min(teoretyczna_produkcja, pojemnosc_magazynu);

    int dostepne_produkty = magazyn + faktyczna_produkcja;
    int sprzedane         = std::min(dostepne_produkty, popyt);

    magazyn = dostepne_produkty - sprzedane;

    if (magazyn > pojemnosc_magazynu)
    {
        magazyn = pojemnosc_magazynu;
    }

    return sprzedane * cena_produktu;
}

void Firma::otrzymaj_przychod()
{
    double przychod = oblicz_przychod();
    stan_konta += przychod;

    historia_przychodow.push_back(przychod);
    if (historia_przychodow.size() > N_MIESIECY)
    {
        historia_przychodow.erase(historia_przychodow.begin());
    }
}

double Firma::oblicz_zadluzenie() const
{
    double zadluzenie = 0;
    for (const auto& kredyt : kredyty)
    {
        zadluzenie += kredyt->get_pozostaly_dlug();
    }
    return zadluzenie;
}

void Firma::drukuj_pracownikow() const
{
    std::cout << "Podsumowanie pracownikow:\n";
    std::cout << "Inzynierowie: " << n_inz << "\n";
    std::cout << "Magazynierowie: " << n_mag << "\n";
    std::cout << "Marketerzy: " << n_mkt << "\n";
    std::cout << "Robotnicy: " << n_rob << "\n";
    for (const auto& pracownik : pracownicy)
    {
        pracownik->print();
    }
}

void Firma::drukuj_informacje() const
{
    int cena_produktu         = n_inz * CI;
    int popyt                 = n_mkt * CMkt;
    int teoretyczna_produkcja = n_rob * CR;
    int pojemnosc_magazynu    = n_mag * CMag;

    std::cout << "Informacje o firmie: \n";
    std::cout << "Cena produktu: " << cena_produktu << "\n";
    std::cout << "Popyt: " << popyt << "\n";
    std::cout << "Teoretyczna produkcja: " << teoretyczna_produkcja << "\n";
    std::cout << "Pojemnosc magazynu: " << pojemnosc_magazynu << "\n";
    std::cout << "Magazyn: " << magazyn << "\n";
    std::cout << "Stan konta: " << stan_konta << "\n";
    std::cout << "Zadluzenie: " << oblicz_zadluzenie() << "\n";
    std::cout << "Wartosc spolki (Sredni przychod): " << oblicz_wartosc_spolki()
              << "\n"; // Sredni przychod z ostatnich N miesięcy. To nie jest sredni stan konta!
}

double Firma::get_stan_konta() const
{
    return stan_konta;
}

double Firma::oblicz_wartosc_spolki() const
{
    if (historia_przychodow.empty())
    {
        return 0.0;
    }

    double suma = 0.0;
    for (double przychod : historia_przychodow)
    {
        suma += przychod;
    }
    return suma / historia_przychodow.size();
}
