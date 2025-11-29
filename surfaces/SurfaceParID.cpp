#include "SurfaceParID.h"
#include "../modele/Modele2D.h"
#include "../modele/Nuage.h"
#include "../modele/Surface.h"
#include "../modele/Point.h"
#include <algorithm>

Surface SurfaceParID::construireSurface(const Nuage& nuage, const Modele2D& modele, int surfaceId) const {
    // Collect all points recursively from the nuage
    std::vector<const Point*> points = modele.collecterPointsRecursif(nuage.getId());
    
    // Sort by ID
    std::sort(points.begin(), points.end(), [](const Point* a, const Point* b) {
        return a->getId() < b->getId();
    });
    
    // Build list of point IDs
    std::vector<int> pointIds;
    for (const Point* p : points) {
        pointIds.push_back(p->getId());
    }
    
    return Surface(pointIds);
}
