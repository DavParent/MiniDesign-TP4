#pragma once

class Nuage;
class Modele2D;
class Surface;

class SurfaceStrategy {
public:
    virtual ~SurfaceStrategy() = default;
    virtual Surface construireSurface(const Nuage& nuage, const Modele2D& modele, int surfaceId) const = 0;
};
