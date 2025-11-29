#include "AffichageTextures.h"
#include "../modele/Modele2D.h"
#include "../modele/Point.h"
#include "Grille.h"

void AffichageTextures::afficher(const Modele2D& modele, Grille& grille) {
    grille.effacer();

    // Draw surfaces first (as lines)
    for (const auto& surface : modele.getSurfaces()) {
        const auto& pointIds = surface.getPointIds();
        if (pointIds.size() < 2) continue;
        
        // Draw lines connecting consecutive points
        for (size_t i = 0; i < pointIds.size(); ++i) {
            size_t nextIdx = (i + 1) % pointIds.size();
            const Point* p1 = modele.trouverPointParIdConst(pointIds[i]);
            const Point* p2 = modele.trouverPointParIdConst(pointIds[nextIdx]);
            
            if (p1 && p2) {
                grille.tracerLigne(p1->getX(), p1->getY(), p2->getX(), p2->getY());
            }
        }
    }

    // Draw points on top of lines
    for (const auto& p : modele.getPoints()) {
        char tex = modele.texturePrincipalePourPoint(p.getId());
        char symbole = (tex != '\0') ? tex : '.';

        grille.dessinerCaractere(p.getX(), p.getY(), symbole);
    }

    grille.afficher();
}
