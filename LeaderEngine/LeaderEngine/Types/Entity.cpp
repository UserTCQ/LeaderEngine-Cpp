#include "Entity.h"
#include "../Application.h"

using namespace LeaderEngine;

Entity::Entity(const char* name) {
	this->name = (char*)name;
	Application::instance->entities.push_back(this);
	start();
}

Entity::~Entity() {
	Application::instance->entities.remove(this);

	delete[] name;
}

void Entity::start() {
	transform = new Transform();
	addComponent(transform);

	setActive(true);
}

void Entity::update() {
	if (!active)
		return;

	for (auto& comp : components)
		comp.second->update();
}

void Entity::lateUpdate() {
	if (!active)
		return;

	for (auto& comp : components)
		comp.second->lateUpdate();
}

void Entity::render() {
	if (!active)
		return;

	if (!vertArray || !shader)
		return;

	shader->use();
	vertArray->use();

	glm::mat4 mvp = transform->getModelMatrix();

	shader->setMat4("mvp", mvp);

	glDrawElements(GL_TRIANGLES, vertArray->indices.size(), GL_UNSIGNED_INT, (void*)0);
}

void Entity::onClosing() {
	for (auto& comp : components)
		comp.second->onClosing();

	delete shader;
	delete vertArray;
}

void Entity::setActive(bool active) {
	this->active = active;
}

//methods for the entity component system
void Entity::addComponent(Component* component) {
	if (typeid(*component) == typeid(Transform))
		return;

	components[typeid(*component)] = component;
	component->start();
}

void Entity::addComponents(std::vector<Component*> components) {
	for (auto comp : components)
		if (typeid(*comp) == typeid(Transform))
			return;

	for (auto comp : components)
		this->components[typeid(*comp)] = comp;

	for (auto comp : components)
		comp->start();
}

template<typename T>
void Entity::removeComponent() {
	if (typeid(T) == typeid(Transform))
		return;

	components.erase(typeid(T));
}