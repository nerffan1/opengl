#pragma once
#include <memory>
#include <glm/glm.hpp>

class Actor; // forward declaration to avoid heavy includes

// Base factory: defines the contract for creating Actors.
// Subclasses implement Create(...) to construct a concrete Actor.
class ActorFactory
{
public:
    virtual ~ActorFactory() = default;
    virtual std::unique_ptr<Actor> Create() const = 0;
};

// Concrete factory for simpleGas.
class SimpleGasFactory : public ActorFactory
{
public:
    std::unique_ptr<Actor> Create() const override;
};


class triangleFactory : public ActorFactory
{
public:
    std::unique_ptr<Actor> Create() const override;
};


