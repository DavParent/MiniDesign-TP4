#include "AffichageTextures.h"
#include "../modele/Modele2D.h"
#include "../modele/Point.h"
#include "Grille.h"
#include <string>

void AffichageTextures::afficher(const Modele2D& modele, Grille& grille) {
    grille.effacer();

    // Tracer les lignes (surfaces)
    for (const auto& surface : modele.getSurfaces()) {
        const auto& pointIds = surface.getPointIds();
        if (pointIds.size() < 2) continue;
        
        for (size_t i = 0; i < pointIds.size(); ++i) {
            size_t nextIdx = (i + 1) % pointIds.size();
            const Point* p1 = modele.trouverPointParIdConst(pointIds[i]);
            const Point* p2 = modele.trouverPointParIdConst(pointIds[nextIdx]);
            
            if (p1 && p2) {
                grille.tracerLigne(p1->getX(), p1->getY(), p2->getX(), p2->getY());
            }
        }
    }

    // Dessiner les points avec TOUTES leurs textures
    for (const auto& p : modele.getPoints()) {
        std::string tex = modele.textureBrutePourPoint(p.getId());
        std::string symbole = (!tex.empty()) ? tex : ".";

        grille.dessinerSymbole(p.getX(), p.getY(), symbole);
    }

    grille.afficher();
}
