#include "transformengine.h"

#include<eventfactory.h>
#include<componentloader.h>
#include<gameobjectloader.h>
#include<game.h>


using namespace BQ;

TransformEngine::TransformEngine() : Engine()
{
    wrapAround = false;
    bounds = sf::FloatRect(0,0,480,270);
    placeholder = "auto_transform_";
}

std::vector<std::string> TransformEngine::getObjectsInRange() const
{
    return objectsInRange;
}

void TransformEngine::setObjectsInRange(const std::vector<std::string> &value)
{
    objectsInRange = value;
}

sf::FloatRect TransformEngine::getBounds() const
{
    return bounds;
}

void TransformEngine::setBounds(const sf::FloatRect &value)
{
    bounds = value;
}

Transform & TransformEngine::getTransform(int index)
{
    return transforms[index];
}

bool TransformEngine::getWrapAround() const
{
    return wrapAround;
}

void TransformEngine::setWrapAround(bool value)
{
    wrapAround = value;
}

Grid *TransformEngine::getGrid() const
{
    return grid;
}

void TransformEngine::setGrid(Grid *value)
{
    grid = value;
}

void TransformEngine::run()
{
    int scale = grid->getScale();
    float rightEdge =(float) (bounds.left + bounds.width)*scale;
    float leftEdge =(float)  bounds.left*scale;
    float topEdge =(float)  bounds.top*scale;
    float bottomEdge =(float)  (bounds.top + bounds.height)*scale;

    activeComponents.clear();
    objectsInRange.clear();

    activeGridLocations    = grid->getBox(grid->getGridPosition(bounds.left,bounds.top),
                                          grid->getGridPosition(bounds.left + bounds.width,
                                                                bounds.top + bounds.height));


    for(unsigned int i=0; i<transforms.size(); i++)
    {
        //update all the transforms!

        const sf::Vector2f & gpos = transforms[i].getPosition();
        if(bounds.contains(gpos))
        {
            activeComponents.push_back(i);
            objectsInRange.push_back(transforms[i].getParent());
        }


        if(wrapAround)
        {
            if(bounds.height>0 && bounds.width > 0)
            {

                if(leftEdge > gpos.x || rightEdge < gpos.x || topEdge > gpos.y || topEdge < gpos.y )
                {
                   //debug->println("out of bounds");
                    sf::Vector2f pos = transforms[i].getPosition();
                    if(pos.x > rightEdge)
                    {
                        transforms[i].setPosition(sf::Vector2f(leftEdge,pos.y));
                    }
                    if(pos.x < leftEdge)
                    {
                        transforms[i].setPosition(sf::Vector2f(rightEdge,pos.y));
                    }
                    pos = transforms[i].getPosition();
                    if(pos.y > bottomEdge)
                    {
                        transforms[i].setPosition(sf::Vector2f(pos.x,topEdge));
                    }
                    if(pos.y < topEdge)
                    {
                        transforms[i].setPosition(sf::Vector2f(pos.x,bottomEdge));
                    }
                }
            }
        }





    }



}

void TransformEngine::drawDebug()
{
    GameWindow& window = *gameWindow;
    sf::RectangleShape r;

    r.setFillColor(sf::Color::Transparent);
    r.setOutlineThickness(1);
    r.setOutlineColor(sf::Color::Blue);

//    for(unsigned int j=0; j<activeComponents.size(); j++)
//    {
//        int i = activeComponents[j];
//        cross.setPosition(transforms[i].getPosition());
//        cross.update();
//        window.draw(cross);
//        //draw all the transforms!
//        //gameWindow->draw(transforms[i]);
//    }



    for(unsigned int i =0; i<activeGridLocations.size();i++)
    {
        sf::Vector2i & column = activeGridLocations[i];
        sf::FloatRect f = grid->getGridSquare(column);
        r.setPosition(f.left,f.top);
        r.setSize(sf::Vector2f(f.width,f.height));
        window.draw(r);
    }
}

void TransformEngine::updatePositions()
{
    for(unsigned int i=0; i<activeComponents.size(); i++)
    {
        int j = activeComponents[i];
        transforms[j].update();
        transforms[j].move(delta*(transforms[j].step));
        transforms[j].setGridPosition(grid->getGridPosition(transforms[j].getPosition()));
    }
}


Transform &TransformEngine::addTransform()
{
    transforms.resize(transforms.size() + 1);
    if(debug != NULL){
        transforms.back().setDebug(debug);
    }
    transforms.back().index = transforms.size()-1;
    transforms.back().name = placeholder + std::to_string(currentId);
    currentId++;
    return(transforms.back());
}
