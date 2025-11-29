#pragma once

#include "Commande.h"

class CommandeDeplacerPoint : public Commande {
public:
    CommandeDeplacerPoint(int idPoint, int ancienX, int ancienY, int nouveauX, int nouveauY);
    
    void executer(Modele2D& modele) override;
    void annuler(Modele2D& modele) override;

private:
    int m_idPoint;
    int m_ancienX;
    int m_ancienY;
    int m_nouveauX;
    int m_nouveauY;
};
