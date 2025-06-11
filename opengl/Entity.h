#pragma once
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <memory>
#include "Component.h"

class Entity {
public:
    // Add any component (returns base Component pointer)
    Component* addComponent(std::unique_ptr<Component> component);
    Component* getComponent(const std::type_info& type) const;

	virtual void update(const float& dt);
	virtual void draw() const = 0;

private:
    std::vector<std::unique_ptr<Component>> m_components;
};
