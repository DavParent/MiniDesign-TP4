#pragma once
#include <vector>
#include <string> 

class Grille {
public:
    static const int LARGEUR = 30;
    static const int HAUTEUR = 20;

    Grille();
    void effacer();
    void tracerLigne(int x0, int y0, int x1, int y1);
    void afficher() const;
    
    void dessinerSymbole(int x, int y, const std::string& symbole);

private:
    std::vector<std::vector<std::string>> cells_;
};
