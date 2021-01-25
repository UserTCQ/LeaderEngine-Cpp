#pragma once

#include <map>
#include <typeindex>
#include <vector>
#include "Component.h"
#include "Transform.h"
#include "VertexArray.h"
#include "Shader.h"

namespace LeaderEngine {
	class Entity {
	public:
		char* name;

		bool active = true;

		Transform* transform;

		VertexArray* vertArray;
		Shader* shader;

		//constructor and destructor
		Entity(const char* name);
		~Entity();

		//methods
		void start();
		void update();
		void lateUpdate();
		void render();
		void onClosing();

		void setActive(bool active);

		void addComponent(Component* component);
		void addComponents(std::vector<Component*> components);

		template <typename T>
		T* getComponent()
		{
			return (T*)components[typeid(T)];
		}

		template<typename T>
		void removeComponent();
	private:
		std::map<std::type_index, Component*> components;
	};
}