#pragma once
#include "NuageElement.h"
#include <vector>

class Nuage : public NuageElement {
public:
    Nuage(int id, char texture, const std::vector<int>& elementIds);

    char getTexture() const { return texture_; }
    const std::vector<int>& getElementIds() const { return elementIds_; }

private:
    char texture_;
    std::vector<int> elementIds_;  // IDs of NuageElement (can be Points or other Nuages)
};

