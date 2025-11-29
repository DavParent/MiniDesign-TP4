#pragma once

#include "SurfaceStrategy.h"

class SurfaceParDistance : public SurfaceStrategy {
public:
    Surface construireSurface(const Nuage& nuage, const Modele2D& modele, int surfaceId) const override;
};
