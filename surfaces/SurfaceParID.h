#pragma once

#include "SurfaceStrategy.h"

class SurfaceParID : public SurfaceStrategy {
public:
    Surface construireSurface(const Nuage& nuage, const Modele2D& modele, int surfaceId) const override;
};
