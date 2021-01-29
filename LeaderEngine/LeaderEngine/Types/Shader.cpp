#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <logger.h>
#include <cassert>
#include <ldefine.h>
#include <glm/gtc/type_ptr.hpp>

using namespace LeaderEngine;

Shader::Shader(const char* vertSource, const char* fragSource) {
	unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertSource, NULL);
	glCompileShader(vertShader);

	unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragSource, NULL);
	glCompileShader(fragShader);

	handle = glCreateProgram();
	glAttachShader(handle, vertShader);
	glAttachShader(handle, fragShader);
	glLinkProgram(handle);

	glDetachShader(handle, vertShader);
	glDetachShader(handle, fragShader);
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	int numberOfUniforms;

	glGetProgramiv(handle, GL_ACTIVE_UNIFORMS, &numberOfUniforms);

	for (int i = 0; i < numberOfUniforms; i++) {
		int length;
		int size;
		GLenum type;
		
		char name[64];

		glGetActiveUniform(handle, i, sizeof(name), &length, &size, &type, name);

		int location = glGetUniformLocation(handle, name);

		uniformLocations[name] = location;
	}
}

Shader::~Shader() {
	glDeleteShader(handle);
}

void Shader::use() {
	glUseProgram(handle);
}

int Shader::getAttribLocation(const char* attribName) {
	return uniformLocations[(char*)attribName];
}

#pragma region setters

void Shader::setInt(const char* name, int value) {
	int loc = getAttribLocation(name);

	SHADER_ASSERT(name, loc != -1);

	glUniform1i(getAttribLocation(name), value);
}

void Shader::setFloat(const char* name, float value) {
	int loc = getAttribLocation(name);

	SHADER_ASSERT(name, loc != -1);

	glUniform1f(getAttribLocation(name), value);
}

void Shader::setVec2(const char* name, glm::vec2 value) {
	int loc = getAttribLocation(name);

	SHADER_ASSERT(name, loc != -1);

	glUniform2f(getAttribLocation(name), value.x, value.y);
}

void Shader::setVec3(const char* name, glm::vec3 value) {
	int loc = getAttribLocation(name);

	SHADER_ASSERT(name, loc != -1);

	glUniform3f(getAttribLocation(name), value.x, value.y, value.z);
}

void Shader::setVec4(const char* name, glm::vec4 value) {
	int loc = getAttribLocation(name);

	SHADER_ASSERT(name, loc != -1);

	glUniform4f(getAttribLocation(name), value.x, value.y, value.z, value.z);
}

void Shader::setMat3(const char* name, glm::mat3 value) {
	int loc = getAttribLocation(name);

	SHADER_ASSERT(name, loc != -1);

	glUniformMatrix3fv(getAttribLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setMat4(const char* name, glm::mat4 value) {
	int loc = getAttribLocation(name);

	SHADER_ASSERT(name, loc != -1);

	glUniformMatrix4fv(getAttribLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

#pragma endregion