#include "Nuage.h"
#include <algorithm>

Nuage::Nuage(int id, char texture, const std::vector<int>& elementIds)
    : NuageElement(id), texture_(texture), elementIds_(elementIds) { }

void Nuage::ajouterElement(int elementId) {
    // Only add if not already present
    if (std::find(elementIds_.begin(), elementIds_.end(), elementId) == elementIds_.end()) {
        elementIds_.push_back(elementId);
    }
}

void Nuage::retirerElement(int elementId) {
    auto it = std::remove(elementIds_.begin(), elementIds_.end(), elementId);
    elementIds_.erase(it, elementIds_.end());
}

