#include "CommandeFusionnerNuage.h"
#include "../modele/Modele2D.h"

CommandeFusionnerNuage::CommandeFusionnerNuage(const std::vector<int>& idsElements)
    : m_idsElements(idsElements), m_idNuageCree(-1) {}

void CommandeFusionnerNuage::executer(Modele2D& modele) {
    m_idNuageCree = modele.fusionnerPointsDansNuage(m_idsElements);
}

void CommandeFusionnerNuage::annuler(Modele2D& modele) {
    if (m_idNuageCree != -1) {
        modele.supprimerNuage(m_idNuageCree);
    }
}
