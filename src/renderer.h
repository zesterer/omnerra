#ifndef RENDERER_H
#define RENDERER_H

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

using namespace gl;

namespace Omnerra
{
	class Renderer
	{
		public: GLFWwindow* window;

		private: GLuint vertex_array_id;
		private: GLuint vertex_buffer;
		private: const GLfloat vertex_buffer_data[9] = {-1.0f, -1.0f, +0.0f, +1.0f, -1.0f, +0.0f, +0.0f, +1.0f, +0.0f};
		private: GLuint program_id;

		public: Renderer();
		public: void init();
		public: bool run();
		public: void render();
		public: void close();
	};
}

#endif
