#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include "Point.h"

class ModeleScene {
public:
    void initialiserPoints(const std::vector<Point>& pts);

    const std::vector<Point> getPoints() const { return points_; }

    void afficherListePoints(std::ostream& os) const;

    Point* trouverPointParId(int id);

    bool deplacerPoint(int id, int newX, int newY);

    bool supprimerPoint(int id);

private:
    std::vector<Point> points_;
};