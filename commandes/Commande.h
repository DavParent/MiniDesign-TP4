#pragma once

class Modele2D;

class Commande {
public:
    virtual ~Commande() = default;
    virtual void executer(Modele2D& modele) = 0;
    virtual void annuler(Modele2D& modele) = 0;
};
