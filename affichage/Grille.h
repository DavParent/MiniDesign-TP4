#pragma once
#include <vector>

class Grille {
public:
    static const int LARGEUR = 30;
    static const int HAUTEUR = 20;

    Grille();

    void effacer();
    void tracerLigne(int x0, int y0, int x1, int y1);
    void afficher() const;

private:
    std::vector<std::vector<char>>& cells;
};