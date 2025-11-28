#include <iostream>
#include <sstream>
#include <string>

#include "modele/Modele2D.h"
#include "util/Parsing.h"

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

    ModeleScene modele;
    modele.initialiserPoints(points);
    
    // Ce sont différentes textures possibles. Seules les 2 premières sont utilisées dans les scénarios du TP.
    vector<char> texturesNuages = {'o', '#', '$'};
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
            // Déplacement d'un point
            cout << "ID du point à déplacer: ";
            string ligne;
            getline(cin, ligne);
            int id = 0;
            {
                istringstream iss(ligne);
                iss >> id;
            }

            cout << "Nouvelle position (x y): ";
            getline(cin, ligne);

            int x = 0, y = 0;

            if (!ligne.empty() && ligne.front() == '(' && ligne.back() == ')') {
                string inner = ligne.substr(1, ligne.size() - 2); 
                replace(inner.begin(), inner.end(), ',', ' ');    
                istringstream iss(inner);
                iss >> x >> y;
            } else {
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

        } else {
            cout << "Commande inconnue.\n";
        }
    }

    return 0;
}