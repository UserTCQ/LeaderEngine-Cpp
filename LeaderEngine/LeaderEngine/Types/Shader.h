#pragma once

#include <glm/glm.hpp>
#include <unordered_map>

namespace LeaderEngine {
	class Shader {
	public:
		Shader(const char* vertSource, const char* fragSource);
		~Shader();

		void use();

		int getAttribLocation(const char* attribName);

#pragma region setters

		void setInt(const char* name, int value);
		void setFloat(const char* name, float value);
		void setVec2(const char* name, glm::vec2 value);
		void setVec3(const char* name, glm::vec3 value);
		void setVec4(const char* name, glm::vec4 value);
		void setMat3(const char* name, glm::mat3 value);
		void setMat4(const char* name, glm::mat4 value);

#pragma endregion
	private:
		int handle;

		std::unordered_map<char*, int> uniformLocations;
	};
}
