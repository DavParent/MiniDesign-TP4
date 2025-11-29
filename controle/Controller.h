#pragma once

#include "../modele/Modele2D.h"
#include "../affichage/Grille.h"
#include "../commandes/Commande.h"
#include <stack>
#include <memory>
#include <vector>

class Controller {
public:
    Controller();
    
    void initialiserModele(const std::vector<Point>& points);
    
    // Display commands
    void afficherListe();
    void afficherAvecTextures();
    void afficherAvecIDs();
    
    // Modification commands (with undo/redo)
    void deplacer(int id, int newX, int newY);
    void supprimer(int id);
    void fusionner(const std::vector<int>& elementIds);
    
    // Surface creation commands
    void creerSurfacesParID();
    void creerSurfacesParDistance();
    
    // Undo/redo
    void undo();
    void redo();
    
    Modele2D& getModele() { return m_modele; }

private:
    Modele2D m_modele;
    Grille m_grille;
    std::vector<char> m_texturesDisponibles;
    std::stack<std::unique_ptr<Commande>> m_pileUndo;
    std::stack<std::unique_ptr<Commande>> m_pileRedo;
    
    void clearRedoStack();
    void executeCommand(std::unique_ptr<Commande> cmd);
};
