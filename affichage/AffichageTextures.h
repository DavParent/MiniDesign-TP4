#pragma once

#include "AffichageStrategy.h"

class AffichageTextures : public AffichageStrategy {
public:
    void afficher(const Modele2D& modele, Grille& grille) override;
};
