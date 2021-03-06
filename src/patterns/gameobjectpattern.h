#ifndef GAMEOBJECTPATTERN_H
#define GAMEOBJECTPATTERN_H

#include <factorypattern.h>
#include <spriterendererpattern.h>
#include <collidablepattern.h>
#include <rigidbodypattern.h>
#include <rayemitterpattern.h>
#include <gamelogicpattern.h>

namespace BQ
{

class GameObjectPattern : public FactoryPattern
{
public:
    GameObjectPattern();

    bool parseFromJson(std::string);

    SpriteRendererPattern parseSpriteRenderer(rapidjson::Value &);
    CollidablePattern parseCollidable(rapidjson::Value &);

    std::string typeName;

    std::vector<SpriteRendererPattern> spriteRendererPatterns;
    std::vector<CollidablePattern> collidablePatterns;
    std::vector<RigidBodyPattern> rigidBodyPatterns;
    std::vector<RayEmitterPattern> rayEmitterPatterns;
    std::vector<GameLogicPattern> gameLogicPatterns;

};
}

#endif // GAMEOBJECTPATTERN_H
