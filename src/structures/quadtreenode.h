#ifndef QUADTREENODE_H
#define QUADTREENODE_H

#include <collidable.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <indexedboundingbox.h>

namespace BQ{
class QuadtreeNode
{
public:
    QuadtreeNode();
    QuadtreeNode(sf::FloatRect);

    int level;
    void addObject(const Collidable &, int index);
    void addObject(IndexedBoundingBox);
    std::vector<IndexedBoundingBox> objects;
    std::vector<QuadtreeNode> nodes;

    void setBounds(sf::FloatRect);

    sf::FloatRect bounds;

    void split();
    void clear();

    void subdivide();

private:


};
}

#endif // QUADTREENODE_H
