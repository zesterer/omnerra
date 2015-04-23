#ifndef RENDERER_H
#define RENDERER_H

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

#include "glm/mat4x4.hpp"

using namespace gl;

namespace Omnerra
{
	class Renderer
	{
		public: GLFWwindow* window;

		private: GLuint vertex_array_id;
		private: GLuint colour_array_id;
		private: GLuint vertex_buffer;
		private: GLuint colour_buffer;
		private: const GLfloat vertex_buffer_data[9] = {-1.0f, -1.0f, +0.0f, +1.0f, -1.0f, +0.0f, +0.0f, +1.0f, +0.0f};
		private: GLuint program_id;
		private: GLuint matrix_id;
		private: glm::mat4 original_vector;
		private: float angle;

		public: Renderer();
		public: void init();
		public: bool run();
		public: void render();
		public: void close();
	};
}

#endif
