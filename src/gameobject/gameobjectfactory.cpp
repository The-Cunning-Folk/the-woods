#include "gameobjectfactory.h"

using namespace BQ;

GameObjectFactory::GameObjectFactory()
{

}

void GameObjectFactory::setStack(GameObjectStack * stack)
{
    gameObjects = stack;
}

void GameObjectFactory::setDebug(DebugUtils *value)
{
    debug = value;
}

void GameObjectFactory::newObject()
{
    GameObject* object = gameObjects->addObject();
    debug->println("generated object: " + object->name);
}
