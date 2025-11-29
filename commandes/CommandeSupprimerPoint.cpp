#include "CommandeSupprimerPoint.h"
#include "../modele/Modele2D.h"

CommandeSupprimerPoint::CommandeSupprimerPoint(int idPoint, int xAvant, int yAvant, const std::vector<int>& idsNuagesAvant)
    : m_idPoint(idPoint), m_xAvant(xAvant), m_yAvant(yAvant), m_idsNuagesAvant(idsNuagesAvant) {}

void CommandeSupprimerPoint::executer(Modele2D& modele) {
    modele.supprimerPoint(m_idPoint);
    // Note: The point is also removed from nuages automatically by model logic
    // or we need to handle it here if not
}

void CommandeSupprimerPoint::annuler(Modele2D& modele) {
    // Recreate the point with its original ID and position
    modele.ajouterPointAvecID(m_idPoint, m_xAvant, m_yAvant);
    
    // Re-add point to all nuages it belonged to
    for (int nuageId : m_idsNuagesAvant) {
        modele.ajouterElementDansNuage(nuageId, m_idPoint);
    }
}
