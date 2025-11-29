#include "Controller.h"
#include "../affichage/AffichageTextures.h"
#include "../affichage/AffichageIDs.h"
#include "../surfaces/SurfaceParID.h"
#include "../surfaces/SurfaceParDistance.h"
#include "../commandes/CommandeDeplacerPoint.h"
#include "../commandes/CommandeSupprimerPoint.h"
#include <iostream>

Controller::Controller() {
    m_texturesDisponibles = {'o', '#', '$', '@', '*'};
}

void Controller::initialiserModele(const std::vector<Point>& points) {
    m_modele.initialiserPoints(points);
}

void Controller::afficherListe() {
    m_modele.afficherListePoints(std::cout);
}

void Controller::afficherAvecTextures() {
    AffichageTextures strategie;
    strategie.afficher(m_modele, m_grille);
}

void Controller::afficherAvecIDs() {
    AffichageIDs strategie;
    strategie.afficher(m_modele, m_grille);
}

void Controller::deplacer(int id, int newX, int newY) {
    Point* p = m_modele.trouverPointParId(id);
    if (!p) {
        std::cout << "Erreur: aucun point avec l'ID " << id << ".\n";
        return;
    }
    
    int oldX = p->getX();
    int oldY = p->getY();
    
    auto cmd = std::make_unique<CommandeDeplacerPoint>(id, oldX, oldY, newX, newY);
    executeCommand(std::move(cmd));
}

void Controller::supprimer(int id) {
    Point* p = m_modele.trouverPointParId(id);
    if (!p) {
        std::cout << "Erreur: aucun point avec l'ID " << id << ".\n";
        return;
    }
    
    int x = p->getX();
    int y = p->getY();
    std::vector<int> nuages = m_modele.getNuagesContenant(id);
    
    auto cmd = std::make_unique<CommandeSupprimerPoint>(id, x, y, nuages);
    executeCommand(std::move(cmd));
}

void Controller::fusionner(const std::vector<int>& elementIds) {
    int nuageId = m_modele.fusionnerPointsDansNuage(elementIds);
    if (nuageId == -1) {
        std::cout << "Erreur: IDs invalides ou fusion impossible.\n";
    }
}

void Controller::creerSurfacesParID() {
    m_modele.viderSurface();
    SurfaceParID strategie;
    
    for (const auto& nuage : m_modele.getNuages()) {
        int surfaceId = m_modele.getProchainIdSurface();
        Surface surface = strategie.construireSurface(nuage, m_modele, surfaceId);
        m_modele.ajouterSurface(surface);
    }
    
    std::cout << "Surfaces créées selon l'ordre des IDs.\n";
}

void Controller::creerSurfacesParDistance() {
    m_modele.viderSurface();
    SurfaceParDistance strategie;
    
    for (const auto& nuage : m_modele.getNuages()) {
        int surfaceId = m_modele.getProchainIdSurface();
        Surface surface = strategie.construireSurface(nuage, m_modele, surfaceId);
        m_modele.ajouterSurface(surface);
    }
    
    std::cout << "Surfaces créées selon la distance minimale.\n";
}

void Controller::undo() {
    if (m_pileUndo.empty()) {
        std::cout << "Rien à annuler.\n";
        return;
    }
    
    std::unique_ptr<Commande> cmd = std::move(m_pileUndo.top());
    m_pileUndo.pop();
    
    cmd->annuler(m_modele);
    m_pileRedo.push(std::move(cmd));
    
    std::cout << "Commande annulée.\n";
}

void Controller::redo() {
    if (m_pileRedo.empty()) {
        std::cout << "Rien à refaire.\n";
        return;
    }
    
    std::unique_ptr<Commande> cmd = std::move(m_pileRedo.top());
    m_pileRedo.pop();
    
    cmd->executer(m_modele);
    m_pileUndo.push(std::move(cmd));
    
    std::cout << "Commande refaite.\n";
}

void Controller::clearRedoStack() {
    while (!m_pileRedo.empty()) {
        m_pileRedo.pop();
    }
}

void Controller::executeCommand(std::unique_ptr<Commande> cmd) {
    cmd->executer(m_modele);
    m_pileUndo.push(std::move(cmd));
    clearRedoStack();
}
