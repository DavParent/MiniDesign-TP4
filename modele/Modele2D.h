#pragma once

#include <vector>
#include <iostream>
#include <string>

#include "Point.h"
#include "Nuage.h"
#include "Surface.h"

class Modele2D {
public:
    void initialiserPoints(const std::vector<Point>& pts);

    const std::vector<Point>& getPoints() const { return points_; }
    const std::vector<Nuage>& getNuages() const { return nuages_; }

    void afficherListePoints(std::ostream& os) const;

    Point* trouverPointParId(int id);
    const Point* trouverPointParIdConst(int id) const;
    bool deplacerPoint(int id, int newX, int newY);
    bool supprimerPoint(int id);

    bool fusionnerPointsDansNuage(const std::vector<int>& ids);

    char texturePrincipalePourPoint(int pointId) const;

    void viderSurface();
    void ajouterSurface(const Surface& s);

private:
    std::vector<Point> points_;
    std::vector<Nuage> nuages_;
    std::vector<Surface> surfaces_;

    std::vector<char> texturesNuages_ {'o', '#'};
    std::size_t nextTextureIndex_ = 0;

    std::string texturesPourPoint(int pointId) const;
};

