#pragma once

#include <vector>
#include <iostream>
#include <string>

#include "Point.h"
#include "Nuage.h"
#include "Surface.h"
#include "NuageElement.h"

class Modele2D {
public:
    Modele2D() : m_prochainIdElement(0), m_prochainIdSurface(0) {}

    void initialiserPoints(const std::vector<Point>& pts);
    void ajouterPoint(int x, int y);
    void ajouterPointAvecID(int id, int x, int y);

    const std::vector<Point>& getPoints() const { return points_; }
    const std::vector<Nuage>& getNuages() const { return nuages_; }
    const std::vector<Surface>& getSurfaces() const { return surfaces_; }

    void afficherListePoints(std::ostream& os) const;

    Point* trouverPointParId(int id);
    const Point* trouverPointParIdConst(int id) const;
    Nuage* trouverNuageParId(int id);
    const Nuage* trouverNuageParIdConst(int id) const;
    NuageElement* trouverElementParId(int id);
    
    bool deplacerPoint(int id, int newX, int newY);
    bool supprimerPoint(int id);
    bool supprimerNuage(int id);

    int fusionnerPointsDansNuage(const std::vector<int>& elementIds);
    std::vector<int> getNuagesContenant(int elementId) const;
    std::vector<const Point*> collecterPointsRecursif(int nuageId) const;

    char texturePrincipalePourPoint(int pointId) const;

    void viderSurface();
    void ajouterSurface(const Surface& s);

    int getProchainIdSurface() { return m_prochainIdSurface++; }

private:
    int m_prochainIdElement;
    int m_prochainIdSurface;
    
    std::vector<Point> points_;
    std::vector<Nuage> nuages_;
    std::vector<Surface> surfaces_;

    std::vector<char> texturesNuages_ {'o', '#'};
    std::size_t nextTextureIndex_ = 0;

    std::string texturesPourPoint(int pointId) const;
    void collecterPointsRecursifHelper(int elementId, std::vector<const Point*>& result) const;
};


