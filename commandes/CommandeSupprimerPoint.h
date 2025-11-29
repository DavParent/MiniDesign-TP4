#pragma once

#include "Commande.h"
#include <vector>

class CommandeSupprimerPoint : public Commande {
public:
    CommandeSupprimerPoint(int idPoint, int xAvant, int yAvant, const std::vector<int>& idsNuagesAvant);
    
    void executer(Modele2D& modele) override;
    void annuler(Modele2D& modele) override;

private:
    int m_idPoint;
    int m_xAvant;
    int m_yAvant;
    std::vector<int> m_idsNuagesAvant;
};
