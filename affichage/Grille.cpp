#include "Grille.h"
#include <cmath>
#include <iostream>

using namespace std;

void Grille::effacer(){
    for (int y = 0; y < HAUTEUR; y++) {
        for (int x = 0; x < LARGEUR; x++){
            cells[y][x] = ' ';
        }
    }
}

void Grille::tracerLigne(int x0, int y0, int x1, int y1) {
    // Distance verticale
    int lignes = abs(y1 - y0);
    // Si la ligne est horizontale 
    if (lignes == 0) {
        // On prend distance horizontale 
        lignes = abs(x1 - x0);
        for (int i = 0; i <= lignes; ++i) {
            // On trace chaque point de la ligne, de gauche à droite ou de droite à gauche selon la direction.
            int x = (x0 < x1) ? x0 + i : x0 - i;
            if (y1 >= 0 && y1 < HAUTEUR && x >= 0 && x < LARGEUR)
                cells[y1][x] = '/';
        }
    } else {
        // Si la ligne est verticale ou diagonale 
        for (int i = 0; i <= lignes; ++i) {
            double t = (double)i / lignes;
            // On fait une interpolation lineaire
            int x = round(x0 + t * (x1 - x0));
            int y = round(y0 + t * (y1 - y0));
            if (x >= 0 && x < LARGEUR && y >= 0 && y < HAUTEUR)
                cells[y][x] = '/';
        }
    }
}

void Grille::afficher() const{
    for (int y = HAUTEUR - 1; y >= 0; --y) {
        for (int x = 0; x < LARGEUR; ++x)
            cout << cells[y][x];
        cout << '\n';
    }
};
