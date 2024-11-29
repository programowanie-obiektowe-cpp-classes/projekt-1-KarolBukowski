#include "Gra.hpp"

int main()
{
    Gra gra;

    // Główna pętla gry
    while (gra.get_stan())
    {
        gra.akcja_gracza();
        gra.tick();
    }

    return 0;
}
