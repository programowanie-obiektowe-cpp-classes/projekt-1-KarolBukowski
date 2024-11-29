#ifndef KREDYT_HPP
#define KREDYT_HPP

class Kredyt
{
public:
    Kredyt(double kwota, int raty, double oprocentowanie);

    double splac_rate();
    bool   czy_splacony() const;
    double get_pozostaly_dlug() const;

private:
    double wysokosc_raty;
    int    pozostale_raty;
};

#endif // KREDYT_HPP
