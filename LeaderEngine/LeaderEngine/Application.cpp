#include <stdlib.h>
#include <stdio.h>
#include <logger.h>
#include <string>
#include "Application.h"
#include "Time.h"

using namespace LeaderEngine;

void Application::start(int width, int height, const char* title, void (*loadCallback)()) 
{
	if (instance)
		return;

	instance = this;

	if (!glfwInit())
		exit(EXIT_FAILURE);

	Time::timeScale = 1;
	this->loadCallback = loadCallback;

	//window creation
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	if (glewInit() != GLEW_OK) 
		exit(EXIT_FAILURE);

	Logger::log(std::string("Vendor: ") + (const char*)glGetString(GL_VENDOR));
	Logger::log(std::string("Renderer: ") + (const char*)glGetString(GL_RENDERER));
	Logger::log(std::string("Version: ") + (const char*)glGetString(GL_VERSION));

	load();

	while (!glfwWindowShouldClose(window)) {
		lastTime = glfwGetTime();

		update();
		render();

		Time::deltaTimeUnscaled = glfwGetTime() - lastTime;
		Time::deltaTime = Time::deltaTimeUnscaled * Time::timeScale;
	}

	//cleanup
	onClosing();

	glfwDestroyWindow(window);
	glfwTerminate();

	exit(EXIT_SUCCESS);
}

void Application::load() 
{
	glEnable(GL_DEPTH_TEST);

	if (loadCallback)
		(*loadCallback)();
}

void Application::update() 
{
	for (auto go : entities)
		if (go->active)
			go->update();

	for (auto go : entities)
		if (go->active)
			go->lateUpdate();
}

void Application::render() 
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto go : entities)
		if (go->active)
			go->render();

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Application::onClosing() {
	for (auto go : entities)
		go->onClosing();
}
