#pragma once

class Modele2D;
class Grille;

class AffichageStrategy {
public:
    virtual ~AffichageStrategy() = default;
    virtual void afficher(const Modele2D& modele, Grille& grille) = 0;
};
