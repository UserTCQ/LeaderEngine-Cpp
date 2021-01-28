#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Component.h";

using namespace glm;

namespace LeaderEngine {
	class Transform : public Component {
	public:
		vec3 position = vec3(0.0);
		quat rotation = quat(0.0, 0.0, 0.0, 0.0);
		vec3 scale = vec3(1.0);

		mat4 getModelMatrix();
	};
}