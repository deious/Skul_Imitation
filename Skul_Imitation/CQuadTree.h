#pragma once
#include "pch.h"

struct Tile {
    int x, y, type;
};

class CQuadTree {
public:
    CQuadTree(RECT bounds, int maxObjects, int maxLevels, int level = 0);
    virtual ~CQuadTree();

    void                Insert(const Tile& tile);
    void                Query(const RECT& area, std::vector<Tile>& foundTiles);

private:
    void                Subdivide();
    bool                Intersects(const RECT& a, const RECT& b) const;

    RECT                m_Bounds;
    int                 m_Level;
    int                 m_MaxObjects;
    int                 m_MaxLevels;
    std::vector<Tile>   m_Objects;
    CQuadTree*          m_Children[4] = { nullptr };
};
