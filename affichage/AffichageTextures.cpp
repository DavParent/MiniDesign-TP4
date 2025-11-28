#include "AffichageTextures.h"
#include "../modele/Modele2D.h"
#include "../modele/Point.h"
#include "Grille.h"

void AffichageTextures::afficher(const Modele2D& modele, Grille& grille) {
    grille.effacer();

    for (const auto& p : modele.getPoints()) {
        char tex = modele.texturePrincipalePourPoint(p.getId());
        char symbole = (tex != '\0') ? tex : '.';

        grille.dessinerCaractere(p.getX(), p.getY(), symbole);
    }

    // Plus tard: tracer aussi les surfaces (c1/c2) avec grille.tracerLigne()

    grille.afficher();
}
