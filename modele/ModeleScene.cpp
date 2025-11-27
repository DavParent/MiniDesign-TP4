#include "ModeleScene.h"
using namespace std;

void ModeleScene::initialiserPoints(const std::vector<Point>& pts){
    points_ = pts;
}
void ModeleScene::afficherListePoints(std::ostream& os) const {
    os << "Liste:\n";
    for (const auto& p : points_) {
        os << p.getId() << ": ("
           << p.getX() << "," << p.getY()
           << ") textures:\n";
    } 
}