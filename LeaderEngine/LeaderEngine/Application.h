#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <list>
#include "Types/Entity.h"

namespace LeaderEngine 
{
	class Application
	{
	public:
		static inline Application *instance;

		GLFWwindow* window;

		void (*loadCallback)();

		std::list<Entity*> entities;

		void start(int width, int height, const char* title, void (*loadCallback)());
	private:
		float lastTime;

		void load();
		void update();
		void render();
		void onClosing();
	};
}