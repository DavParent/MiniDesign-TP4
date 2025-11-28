#include "Modele2D.h"
#include <algorithm>

using namespace std;

void Modele2D::initialiserPoints(const std::vector<Point>& pts){
    points_ = pts;
}
void Modele2D::afficherListePoints(std::ostream& os) const {
    os << "Liste:\n";
    for (const auto& p : points_) {
        os << p.getId() << ": ("
           << p.getX() << "," << p.getY()
           << ") textures:";

        string tex = texturesPourPoint(p.getId());
        if (!tex.empty()) {
            os << " " << tex;
        }
        os << "\n";
    }

    for (const auto& n : nuages_) {
        os << "Nuage '" << n.getTexture() << "' contient les points: ";
        const auto& ids = n.getPointIds();
        for (size_t i = 0; i < ids.size(); ++i) {
            os << ids[i];
            if (i + 1 < ids.size())
                os << ", ";
        }
        os << "\n";
    }
}    

Point* Modele2D::trouverPointParId(int id) {
    for (auto& p : points_) {
        if (p.getId() == id)
            return &p;
    }
    return nullptr;
}

const Point* Modele2D::trouverPointParIdConst(int id) const {
    for (const auto& p : points_) {
        if (p.getId() == id)
            return &p;
    }
    return nullptr;
}

bool Modele2D::deplacerPoint(int id, int newX, int newY) {
    Point* p = trouverPointParId(id);
    if (!p) return false;
    p->setPosition(newX, newY);
    return true;
}

bool Modele2D::supprimerPoint(int id) {
    auto it = std::remove_if(points_.begin(), points_.end(),
                             [id](const Point& p) {
                                 return p.getId() == id;
                             });
    if (it == points_.end())
        return false;

    points_.erase(it, points_.end());
    return true;
}

string Modele2D::texturesPourPoint(int pointId) const {
    string result;
    bool first = true;
    for (const auto& n : nuages_) {
        const auto& ids = n.getPointIds();
        if(find(ids.begin(), ids.end(), pointId) != ids.end()){
            if (!first)
                result += " ";
            result += "'";
            result += n.getTexture();
            result += "'";
            first = false;
        }
    }
    return result;
}

bool Modele2D::fusionnerPointsDansNuage(const vector<int>& ids) {
    if (ids.empty()) return false;

    for (int id : ids) {
        if (!trouverPointParId(id)){
            return false;
        }
    }

    if (texturesNuages_.empty())
        return false;

    char texture = texturesNuages_[nextTextureIndex_ % texturesNuages_.size()];
    ++nextTextureIndex_;

    nuages_.emplace_back(texture, ids);
    return true;
}

char Modele2D::texturePrincipalePourPoint(int pointId) const {
    for (const auto& n : nuages_) {
        const auto& ids = n.getPointIds();
        if (std::find(ids.begin(), ids.end(), pointId) != ids.end()) {
            return n.getTexture();
        }
    }
    return '\0';
}

void Modele2D::viderSurface(){
    surfaces_.clear();
}

void Modele2D::ajouterSurface(const Surface& s){
    surfaces_.push_back(s);
}
