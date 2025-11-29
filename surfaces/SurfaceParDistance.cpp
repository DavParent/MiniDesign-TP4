#include "SurfaceParDistance.h"
#include "../modele/Modele2D.h"
#include "../modele/Nuage.h"
#include "../modele/Surface.h"
#include "../modele/Point.h"
#include <cmath>
#include <limits>
#include <algorithm>

Surface SurfaceParDistance::construireSurface(const Nuage& nuage, const Modele2D& modele, int surfaceId) const {
    // Collect all points recursively from the nuage
    std::vector<const Point*> points = modele.collecterPointsRecursif(nuage.getId());
    
    if (points.empty()) {
        return Surface(std::vector<int>());
    }
    
    // Nearest neighbor algorithm
    std::vector<int> pointIds;
    std::vector<bool> visited(points.size(), false);
    
    // Start with the first point
    int currentIdx = 0;
    visited[currentIdx] = true;
    pointIds.push_back(points[currentIdx]->getId());
    
    // Find nearest unvisited neighbor for each step
    for (size_t step = 1; step < points.size(); ++step) {
        double minDist = std::numeric_limits<double>::max();
        int nearestIdx = -1;
        
        const Point* current = points[currentIdx];
        
        for (size_t i = 0; i < points.size(); ++i) {
            if (!visited[i]) {
                const Point* candidate = points[i];
                double dx = candidate->getX() - current->getX();
                double dy = candidate->getY() - current->getY();
                double dist = std::sqrt(dx * dx + dy * dy);
                
                if (dist < minDist) {
                    minDist = dist;
                    nearestIdx = i;
                }
            }
        }
        
        if (nearestIdx != -1) {
            visited[nearestIdx] = true;
            pointIds.push_back(points[nearestIdx]->getId());
            currentIdx = nearestIdx;
        }
    }
    
    return Surface(pointIds);
}
