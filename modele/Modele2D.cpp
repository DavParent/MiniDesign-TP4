#include "Modele2D.h"
#include <algorithm>

using namespace std;

void Modele2D::initialiserPoints(const std::vector<Point>& pts){
    points_.clear();
    for (const auto& p : pts) {
        ajouterPoint(p.getX(), p.getY());
    }
}

void Modele2D::ajouterPoint(int x, int y) {
    points_.emplace_back(m_prochainIdElement++, x, y);
}

void Modele2D::ajouterPointAvecID(int id, int x, int y) {
    points_.emplace_back(id, x, y);
    if (id >= m_prochainIdElement) {
        m_prochainIdElement = id + 1;
    }
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
        os << "Nuage " << n.getId() << " '" << n.getTexture() << "' contient les elements: ";
        const auto& ids = n.getElementIds();
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

Nuage* Modele2D::trouverNuageParId(int id) {
    for (auto& n : nuages_) {
        if (n.getId() == id)
            return &n;
    }
    return nullptr;
}

const Nuage* Modele2D::trouverNuageParIdConst(int id) const {
    for (const auto& n : nuages_) {
        if (n.getId() == id)
            return &n;
    }
    return nullptr;
}

NuageElement* Modele2D::trouverElementParId(int id) {
    Point* p = trouverPointParId(id);
    if (p) return p;
    return trouverNuageParId(id);
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

bool Modele2D::supprimerNuage(int id) {
    auto it = std::remove_if(nuages_.begin(), nuages_.end(),
                             [id](const Nuage& n) {
                                 return n.getId() == id;
                             });
    if (it == nuages_.end())
        return false;

    nuages_.erase(it, nuages_.end());
    return true;
}

string Modele2D::texturesPourPoint(int pointId) const {
    string result;
    bool first = true;
    for (const auto& n : nuages_) {
        const auto& ids = n.getElementIds();
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

int Modele2D::fusionnerPointsDansNuage(const vector<int>& elementIds) {
    if (elementIds.empty()) return -1;

    for (int id : elementIds) {
        if (!trouverElementParId(id)){
            return -1;
        }
    }

    if (texturesNuages_.empty())
        return -1;

    char texture = texturesNuages_[nextTextureIndex_ % texturesNuages_.size()];
    ++nextTextureIndex_;

    int nuageId = m_prochainIdElement++;
    nuages_.emplace_back(nuageId, texture, elementIds);
    return nuageId;
}

std::vector<int> Modele2D::getNuagesContenant(int elementId) const {
    std::vector<int> result;
    for (const auto& n : nuages_) {
        const auto& ids = n.getElementIds();
        if (std::find(ids.begin(), ids.end(), elementId) != ids.end()) {
            result.push_back(n.getId());
        }
    }
    return result;
}

std::vector<const Point*> Modele2D::collecterPointsRecursif(int nuageId) const {
    std::vector<const Point*> result;
    collecterPointsRecursifHelper(nuageId, result);
    return result;
}

void Modele2D::collecterPointsRecursifHelper(int elementId, std::vector<const Point*>& result) const {
    const Point* p = trouverPointParIdConst(elementId);
    if (p) {
        result.push_back(p);
        return;
    }
    
    const Nuage* n = trouverNuageParIdConst(elementId);
    if (n) {
        for (int childId : n->getElementIds()) {
            collecterPointsRecursifHelper(childId, result);
        }
    }
}

char Modele2D::texturePrincipalePourPoint(int pointId) const {
    for (const auto& n : nuages_) {
        const auto& ids = n.getElementIds();
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

