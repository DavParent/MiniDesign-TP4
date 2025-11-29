#include "AffichageIDs.h"
#include "../modele/Modele2D.h"
#include "../modele/Point.h"
#include "Grille.h"
#include <string> // Nécessaire pour std::string et std::to_string

void AffichageIDs::afficher(const Modele2D& modele, Grille& grille) {
    grille.effacer();

    // Tracer les surfaces en premier (lignes)
    for (const auto& surface : modele.getSurfaces()) {
        const auto& pointIds = surface.getPointIds();
        if (pointIds.size() < 2) continue;
        
        // Tracer les lignes reliant les points consécutifs
        for (size_t i = 0; i < pointIds.size(); ++i) {
            size_t nextIdx = (i + 1) % pointIds.size();
            const Point* p1 = modele.trouverPointParIdConst(pointIds[i]);
            const Point* p2 = modele.trouverPointParIdConst(pointIds[nextIdx]);
            
            if (p1 && p2) {
                grille.tracerLigne(p1->getX(), p1->getY(), p2->getX(), p2->getY());
            }
        }
    }

    // Tracer les IDs des points par-dessus les lignes
    for (const auto& p : modele.getPoints()) {
        int id = p.getId();
        
        // CORRECTION : Conversion de l'ID (chiffre unique) en string
        // car Grille::dessinerSymbole attend maintenant une std::string
        std::string symbole = std::to_string(id % 10);

        grille.dessinerSymbole(p.getX(), p.getY(), symbole);
    }

    grille.afficher();
}
