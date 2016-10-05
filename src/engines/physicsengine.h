#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <engine.h>
#include <rigidbody.h>
#include <physicalexchange.h>

namespace BQ{
class PhysicsEngine : public Engine
{
public:
    PhysicsEngine();

    void wake();

    void start();
    void run();
    void finish();

    float grav;

    void addCollision(const PhysicalExchange &);

    std::vector<PhysicalExchange> collisions;

};
}

#endif // PHYSICSENGINE_H
