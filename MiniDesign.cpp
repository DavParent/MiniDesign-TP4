#include <iostream>
#include <sstream>
#include <string>

#include "modele/Modele2D.h"
#include "util/Parsing.h"
#include "affichage/Grille.h"
#include "affichage/AffichageTextures.h"
#include "affichage/AffichageIDs.h"

using namespace std;

int main(int argc, char* argv[]) {
    string args;

    // On accepte des points en entrée.
    if (argc > 1) {
        ostringstream oss;
        for (int i = 1; i < argc; ++i)
            oss << argv[i] << " ";
        args = oss.str();
    } else {
        cout << "Entrez les points au format (x,y) :\n> ";
        getline(cin, args);
    }
    
    vector<Point> points = creerPointsDepuisLigne(args);

    Modele2D modele;
    modele.initialiserPoints(points);
    Grille grille;
    
    // Ce sont différentes textures possibles. Seules les 2 premières sont utilisées dans les scénarios du TP.
    string cmd;
    
    // Menu
    while (true) {
        cout << "\nCommandes:\n"
             << "a  - Afficher les points et les nuages\n"
             << "o1 - Afficher l'orthèse avec les textures des points\n"
             << "o2 - Afficher l'orthèse avec les IDs des points\n"
             << "f  - Fusionner des points dans un nuage (et appliquer texture)\n"
             << "d  - Deplacer un point (ID)\n"
             << "s  - Supprimer un point (ID)\n"
             << "c1 - Créer les surfaces selon l'ordre des IDs\n"
             << "c2 - Créer les surfaces selon la distance minimale\n"
             << "q  - Quitter\n> ";

        getline(cin, cmd);

        if (cmd == "q") {
            break;
        } else if (cmd == "a") {
            modele.afficherListePoints(cout);

        } else if (cmd == "d") {
            cout << "ID du point à déplacer: ";
            string ligne;
            getline(cin, ligne);
            int id;
            {
                istringstream iss(ligne);
                iss >> id;
            }

            cout << "Nouvelle position (x y): ";
            getline(cin, ligne);
            int x, y;
            {
                istringstream iss(ligne);
                iss >> x >> y;
            }

            if (!modele.deplacerPoint(id, x, y)) {
                cout << "Erreur: aucun point avec l'ID " << id << ".\n";
            }

        } else if (cmd == "s") {
            cout << "ID du point à supprimer: ";
            string ligne;
            getline(cin, ligne);
            int id;
            {
                istringstream iss(ligne);
                iss >> id;
            }

            if (!modele.supprimerPoint(id)) {
                cout << "Erreur: aucun point avec l'ID " << id << ".\n";
            }

        } else if (cmd == "f") {
            cout << "IDs des points à fusionner dans un nuage (ex: 0 2 4): ";
            string ligne;
            getline(cin, ligne);
            istringstream iss(ligne);
            vector<int> ids;
            int id;
            while (iss >> id) {
                ids.push_back(id);
            }

            if (!modele.fusionnerPointsDansNuage(ids)) {
                cout << "Erreur: IDs invalides ou fusion impossible.\n";
            }
        } else if (cmd == "o1") {
            AffichageTextures vue;
            vue.afficher(modele, grille);
        } else if (cmd == "o2") {
            AffichageIDs vue;
            vue.afficher(modele, grille);
        } else {
            cout << "Commande inconnue.\n";
        }
    }

    return 0;
}