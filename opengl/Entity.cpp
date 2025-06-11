#include "Entity.h"

Component* Entity::addComponent(std::unique_ptr<Component> component)
{
    component->setEntity(this);
    m_components.push_back(std::move(component));
    return m_components.back().get();
}

Component* Entity::getComponent(const std::type_info& type) const
{
    for (auto& component : m_components) {
        if (typeid(*component) == type) {
            return component.get();
        }
    }
    return nullptr;
}

void Entity::update(const float& dt)
{
	for (const auto& pair : m_components) {
		pair->update(dt);
	}
}
