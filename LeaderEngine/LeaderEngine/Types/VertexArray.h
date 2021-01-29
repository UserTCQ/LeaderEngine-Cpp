#pragma once

#include <span>

namespace LeaderEngine {
	class VertexArray {
	public:
		std::span<float> vertices;
		std::span<unsigned int> indices;

		VertexArray(std::span<float> vertices, std::span<unsigned int> indices);
		~VertexArray();

		void use();
	private:
		unsigned int vbo, ebo, vao;

		void init();
	};
}