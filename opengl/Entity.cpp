#include "Entity.h"

Component* Entity::addComponent(std::unique_ptr<Component> component)
{
    component->setEntity(this);
    mComponents.push_back(std::move(component));
    return mComponents.back().get();
}

Component* Entity::getComponent(const std::type_info& type) const
{
    for (auto& component : mComponents) {
        if (typeid(*component) == type) {
            return component.get();
        }
    }
    return nullptr;
}

void Entity::update(const float& dt)
{
	for (const auto& pair : mComponents) {
		pair->update(dt);
	}
}
