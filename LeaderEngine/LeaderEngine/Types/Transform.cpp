#include "transform.h"
#include <ldefine.h>

using namespace LeaderEngine;

glm::mat4 Transform::getModelMatrix() 
{
	mat4 trans = MAT4_IDENTITY;
	return glm::translate(trans, position) * glm::mat4_cast(rotation) * glm::scale(trans, scale);
}