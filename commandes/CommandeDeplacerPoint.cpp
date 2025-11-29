#include "CommandeDeplacerPoint.h"
#include "../modele/Modele2D.h"

CommandeDeplacerPoint::CommandeDeplacerPoint(int idPoint, int ancienX, int ancienY, int nouveauX, int nouveauY)
    : m_idPoint(idPoint), m_ancienX(ancienX), m_ancienY(ancienY), 
      m_nouveauX(nouveauX), m_nouveauY(nouveauY) {}

void CommandeDeplacerPoint::executer(Modele2D& modele) {
    modele.deplacerPoint(m_idPoint, m_nouveauX, m_nouveauY);
}

void CommandeDeplacerPoint::annuler(Modele2D& modele) {
    modele.deplacerPoint(m_idPoint, m_ancienX, m_ancienY);
}
