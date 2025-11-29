#include "Nuage.h"

Nuage::Nuage(int id, char texture, const std::vector<int>& elementIds)
    : NuageElement(id), texture_(texture), elementIds_(elementIds) { }

