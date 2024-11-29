#include "Kredyt.hpp"

Kredyt::Kredyt(double kwota, int raty, double oprocentowanie) : pozostale_raty(raty)
{
    double calkowity_dlug = kwota * (1 + (oprocentowanie * (pozostale_raty / 12.0)));
    wysokosc_raty         = calkowity_dlug / pozostale_raty;
}

double Kredyt::splac_rate()
{
    if (pozostale_raty > 0)
    {
        pozostale_raty--;
        return wysokosc_raty;
    }
    return 0.0;
}

bool Kredyt::czy_splacony() const
{
    return pozostale_raty == 0;
}

double Kredyt::get_pozostaly_dlug() const
{
    return pozostale_raty * wysokosc_raty;
}
