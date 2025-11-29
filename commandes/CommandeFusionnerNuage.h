#pragma once

#include "Commande.h"
#include <vector>

class CommandeFusionnerNuage : public Commande {
public:
    CommandeFusionnerNuage(const std::vector<int>& idsElements);
    
    void executer(Modele2D& modele) override;
    void annuler(Modele2D& modele) override;

private:
    std::vector<int> m_idsElements;
    int m_idNuageCree;
};
