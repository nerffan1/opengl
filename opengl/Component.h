#pragma once
#include <memory>

class Entity;

class Component {
public:
    virtual ~Component() = default;

    // Core lifecycle methods
    virtual void initialize() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void destroy() = 0;

    // Transformation hierarchy
    virtual void setEntity(Entity* entity) { mEntity = entity; }
    Entity* getEntity() const { return mEntity; }

protected:
    Entity* mEntity = nullptr; // Back reference to owning entity
};

