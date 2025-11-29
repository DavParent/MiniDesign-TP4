#include "Grille.h"
#include <cmath>
#include <iostream>

using namespace std;

// Initialise avec des espaces (chaînes)
Grille::Grille()
    : cells_(HAUTEUR, std::vector<string>(LARGEUR, " ")) { }

void Grille::effacer(){
    for (int y = 0; y < HAUTEUR; y++) {
        for (int x = 0; x < LARGEUR; x++){
            cells_[y][x] = " ";
        }
    }
}

void Grille::tracerLigne(int x0, int y0, int x1, int y1) {
    int lignes = abs(y1 - y0);
    if (lignes == 0) {
        lignes = abs(x1 - x0);
        for (int i = 0; i <= lignes; ++i) {
            int x = (x0 < x1) ? x0 + i : x0 - i;
            if (y1 >= 0 && y1 < HAUTEUR && x >= 0 && x < LARGEUR)
                cells_[y1][x] = "/"; // Utilise une chaîne "/"
        }
    } else {
        for (int i = 0; i <= lignes; ++i) {
            double t = (double)i / lignes;
            int x = round(x0 + t * (x1 - x0));
            int y = round(y0 + t * (y1 - y0));
            if (x >= 0 && x < LARGEUR && y >= 0 && y < HAUTEUR)
                cells_[y][x] = "/"; // Utilise une chaîne "/"
        }
    }
}

void Grille::afficher() const{
    for (int y = HAUTEUR - 1; y >= 0; --y) {
        for (int x = 0; x < LARGEUR; ++x)
            cout << cells_[y][x];
        cout << '\n';
    }
};

// Nouvelle méthode adaptée
void Grille::dessinerSymbole(int x, int y, const std::string& s) {
    if (x >= 0 && x < LARGEUR && y >= 0 && y < HAUTEUR) {
        cells_[y][x] = s;
    }
};
