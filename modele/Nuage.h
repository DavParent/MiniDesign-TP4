#pragma once
#include <vector>

class Nuage {
public:
    Nuage(char texture, const std::vector<int>& pointIds);

    char getTexture() const { return texture_; }
    const std::vector<int>& getPointIds() const { return pointIds_; }

private:
    char texture_;
    std::vector<int> pointIds_;
};
