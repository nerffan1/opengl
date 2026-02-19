#include "ActorFactory.h"
#include "SimpleGas.h"
#include "Triangle.h"
#include "window.h"

std::unique_ptr<Actor> SimpleGasFactory::Create() const
{
    //TODO: Parametrize screen values
    return std::make_unique<simpleGas>(
        glm::vec3(-100.0/2, -100.0/2, 0.0f),
        glm::vec3(100.0/2, 100.0/2, 0.0f),
        8,
        3000);
}

std::unique_ptr<Actor> triangleFactory::Create() const
{
    return std::make_unique<Triangle>();
}
