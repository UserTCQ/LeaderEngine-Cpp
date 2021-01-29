#pragma once

#define MAT4_IDENTITY glm::mat4(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0)

#define SHADER_ASSERT(name, x) if (!(x)) { Logger::log("ERROR: Uniform " + std::string(name) + "does not exist!"); assert(x); }