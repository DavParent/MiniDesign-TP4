#include "AffichageIDs.h"
#include "../modele/Modele2D.h"
#include "../modele/Point.h"
#include "Grille.h"

void AffichageIDs::afficher(const Modele2D& modele, Grille& grille) {
    grille.effacer();

    for (const auto& p : modele.getPoints()) {
        int id = p.getId();
        char symbole = '0' + (id % 10);

        grille.dessinerCaractere(p.getX(), p.getY(), symbole);
    }

    // Plus tard: tracer aussi les surfaces

    grille.afficher();
}
