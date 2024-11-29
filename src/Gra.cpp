#include "Gra.hpp"

std::default_random_engine       generator;
std::uniform_int_distribution<>  bool_dist(0, 1);
std::uniform_int_distribution<>  follows_dist(0, 1000);
std::uniform_real_distribution<> but_dist(40.0, 45.0);

Gra::Gra() : firma(std::make_unique< Firma >()), stan(true)
{}

void Gra::akcja_gracza()
{
    std::string komenda;
    std::cout << "\n Wpisz komende: ";
    std::cin >> komenda;

    if (komenda == "lp")
    {
        firma->drukuj_pracownikow();
    }
    else if (komenda == "zinz")
    {
        firma->zatrudnij(std::make_unique< Inz >("Karol Bukowski", "MEiL"));
    }
    else if (komenda == "zmag")
    {
        firma->zatrudnij(std::make_unique< Mag >("Karol Bukowski", bool_dist(generator) == 1));
    }
    else if (komenda == "zmkt")
    {
        firma->zatrudnij(std::make_unique< Mkt >("Karol Bukowski", follows_dist(generator)));
    }
    else if (komenda == "zrob")
    {
        firma->zatrudnij(std::make_unique< Rob >("Karol Bukowski", std::round(but_dist(generator) * 10.0) / 10.0));
    }
    else if (komenda == "kred")
    {
        double kwota;
        int    czas;
        std::cout << "Podaj kwote kredytu: ";
        std::cin >> kwota;
        std::cout << "Podaj czas splaty w miesiacach: ";
        std::cin >> czas;
        firma->wez_kredyt(kwota, czas);
    }
    else if (komenda == "kt")
    {
        double poprzedni_stan_konta = firma->get_stan_konta();

        firma->otrzymaj_przychod();
        firma->zaplac_wynagrodzenie();
        firma->splac_raty();

        double zmiana = firma->get_stan_konta() - poprzedni_stan_konta;

        std::cout << "Stan konta: " << firma->get_stan_konta() << " (" << (zmiana >= 0 ? "+" : "") << zmiana << ")\n";
    }
    else if (komenda == "info")
    {
        firma->drukuj_informacje();
    }
    else if (komenda == "help")
    {
        std::cout << "Dostepne komendy:\n";
        std::cout << "lp - wylistuj pracownikow\n";
        std::cout << "zinz - zatrudnij inzyniera\n";
        std::cout << "zmag - zatrudnij magazyniera\n";
        std::cout << "zmkt - zatrudnij marketera\n";
        std::cout << "zrob - zatrudnij robotnika\n";
        std::cout << "kred - wez kredyt\n";
        std::cout << "kt - zakoncz ture i wyswietl stan firmy\n";
        std::cout << "info - wyswietl informacje o firmie\n";
        std::cout << "help - wyswietl dostepne komendy\n";
    }
    else
    {
        std::cout << "Nieznana komenda." << std::endl;
    }
}

bool Gra::get_stan() const
{
    return stan;
}

void Gra::tick()
{
    if (firma->get_stan_konta() < 0)
    {
        std::cout << "Firma zbankrutowala!\n";
        stan = false;
    }
    else if (firma->oblicz_zadluzenie() > firma->get_stan_konta() * MAX_ZADLUZENIE_MNOZNIK)
    {
        std::cout << "Firma nie moze splacic zadluzenia. Firma zbankrutowala!\n";
        stan = false;
    }
    else
    {
        double wartosc_spolki           = firma->oblicz_wartosc_spolki();
        double wartosc_po_odjeciu_dlugu = wartosc_spolki - firma->oblicz_zadluzenie();

        if (wartosc_po_odjeciu_dlugu >= WARTOSC_DO_ZWYCIESTWA)
        {
            std::cout << "Gratulacje! Twoja firma osiagnela wartosc " << wartosc_po_odjeciu_dlugu
                      << " i zwyciezyles w grze!\n";
            stan = false;
        }
    }
}
