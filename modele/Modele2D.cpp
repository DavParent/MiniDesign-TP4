#include "Modele2D.h"

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

Point* ModeleScene::trouverPointParId(int id) {
    for (auto& p : points_) {
        if (p.getId() == id)
            return &p;
    }
    return nullptr;
}

bool ModeleScene::deplacerPoint(int id, int newX, int newY) {
    Point* p = trouverPointParId(id);
    if (!p) return false;
    p->setPosition(newX, newY);
    return true;
}

bool ModeleScene::supprimerPoint(int id) {
    auto it = std::remove_if(points_.begin(), points_.end(),
                             [id](const Point& p) {
                                 return p.getId() == id;
                             });
    if (it == points_.end())
        return false;

    points_.erase(it, points_.end());
    return true;
}