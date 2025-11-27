#pragma once

#include <vector>
#include <iostream>
#include "Point.h"

class ModeleScene {
public:
    void initialiserPoints(const std::vector<Point>& pts);

    const std::vector<Point> getPoints() const { return points_; }

    void afficherListePoints(std::ostream& os) const;
private:
    std::vector<Point> points_;

};