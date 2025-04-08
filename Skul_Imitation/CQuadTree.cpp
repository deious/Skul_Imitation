#include "pch.h"
#include "CQuadTree.h"

CQuadTree::CQuadTree(RECT bounds, int maxObjects, int maxLevels, int level)
    : m_Bounds(bounds), m_MaxObjects(maxObjects), m_MaxLevels(maxLevels), m_Level(level) {
}

CQuadTree::~CQuadTree() {
    for (auto& child : m_Children) {
        delete child;
    }
}

void CQuadTree::Insert(const Tile& tile) {
    if (m_Children[0]) {
        for (auto& child : m_Children) {
            if (tile.x >= child->m_Bounds.left && tile.x < child->m_Bounds.right &&
                tile.y >= child->m_Bounds.top && tile.y < child->m_Bounds.bottom) {
                child->Insert(tile);
                return;
            }
        }
    }

    m_Objects.push_back(tile);

    if (m_Objects.size() > m_MaxObjects && m_Level < m_MaxLevels) {
        if (!m_Children[0]) Subdivide();

        auto it = m_Objects.begin();
        while (it != m_Objects.end()) {
            bool moved = false;
            for (auto& child : m_Children) {
                if ((*it).x >= child->m_Bounds.left && (*it).x < child->m_Bounds.right &&
                    (*it).y >= child->m_Bounds.top && (*it).y < child->m_Bounds.bottom) {
                    child->Insert(*it);
                    it = m_Objects.erase(it);
                    moved = true;
                    break;
                }
            }
            if (!moved) ++it;
        }
    }
}

void CQuadTree::Query(const RECT& area, std::vector<Tile>& foundTiles) {
    if (!Intersects(m_Bounds, area)) return;

    for (const auto& tile : m_Objects) {
        if (tile.x >= area.left && tile.x < area.right &&
            tile.y >= area.top && tile.y < area.bottom) {
            foundTiles.push_back(tile);
        }
    }

    if (m_Children[0]) {
        for (auto& child : m_Children) {
            child->Query(area, foundTiles);
        }
    }
}

bool CQuadTree::Intersects(const RECT& a, const RECT& b) const {
    return !(a.right < b.left || a.left > b.right || a.bottom < b.top || a.top > b.bottom);
}

void CQuadTree::Subdivide() {
    int halfWidth = (m_Bounds.right - m_Bounds.left) / 2;
    int halfHeight = (m_Bounds.bottom - m_Bounds.top) / 2;

    m_Children[0] = new CQuadTree({ m_Bounds.left, m_Bounds.top, m_Bounds.left + halfWidth, m_Bounds.top + halfHeight }, m_MaxObjects, m_MaxLevels, m_Level + 1);
    m_Children[1] = new CQuadTree({ m_Bounds.left + halfWidth, m_Bounds.top, m_Bounds.right, m_Bounds.top + halfHeight }, m_MaxObjects, m_MaxLevels, m_Level + 1);
    m_Children[2] = new CQuadTree({ m_Bounds.left, m_Bounds.top + halfHeight, m_Bounds.left + halfWidth, m_Bounds.bottom }, m_MaxObjects, m_MaxLevels, m_Level + 1);
    m_Children[3] = new CQuadTree({ m_Bounds.left + halfWidth, m_Bounds.top + halfHeight, m_Bounds.right, m_Bounds.bottom }, m_MaxObjects, m_MaxLevels, m_Level + 1);
}
