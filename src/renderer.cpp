#include "stdio.h"
#include "stdlib.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

#include "renderer.h"
#include "rendertypes.h"
#include "loadshader.h"

using namespace std;

using namespace gl;

namespace Omnerra
{
	Renderer::Renderer()
	{
		printf("Starting Renderer...\n");

		//Start up GLFW
		printf("Initialising GLFW: ");
		if (glfwInit())
		{
			printf("SUCCEEDED\n");
		}
		else
		{
			printf("FAILED\n");
			exit(EXIT_FAILURE);
		}

		printf("Creating window: ");
		if ((this->window = glfwCreateWindow(640, 480, "GLFW Test", NULL, NULL)))
		{
			printf("SUCCEEDED\n");
		}
		else
		{
			printf("FAILED\n");
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		this->init();
	}

	void Renderer::init()
	{
		//Set the OpenGL context within the window as the current one
		glfwMakeContextCurrent(this->window);

		//Initialise glbinding
		glbinding::Binding::initialize();

		glGenVertexArrays(1, &this->vertex_array_id);
		glBindVertexArray(this->vertex_array_id);

		glGenBuffers(1, &this->vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer);

		//Pass the data to GL (the graphics card)
		glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertex_buffer_data), this->vertex_buffer_data, GL_STATIC_DRAW);

		//Load the shaders
		this->program_id = loadShaders( "shaders/simplevertexshader.glsl", "shaders/simplefragmentshader.glsl" );
	}

	bool Renderer::run()
	{
		this->render();

		glfwSwapBuffers(this->window);

		glfwPollEvents();

		return !glfwWindowShouldClose(window);
	}

	void Renderer::render()
	{
		/*RenderTypes::ObjectType cube =
		{
			{
				-10, -10, +10, //Vertex v0
				+10, -10, +10, //Vertex v1
				+10, -10, -10, //Vertex v2
				-10, -10, -10, //Vertex v3
				-10, +10, +10, //Vertex v4
				+10, +10, +10, //Vertex v5
				+10, +10, -10, //Vertex v6
				-10, +10, -10, //Vertex v7
			},
			{
				0, 1, 4, //Polygon
				1, 5, 4, //Polygon
				1, 2, 5, //Polygon
				2, 6, 5, //Polygon
				2, 3, 6, //Polygon
				3, 7, 6, //Polygon
				3, 0, 7, //Polygon
				0, 4, 7, //Polygon
				4, 5, 7, //Polygon
				5, 6, 7, //Polygon
				3, 2, 0, //Polygon
				2, 1, 0, //Polygon
			}
		};*/

		//Clear the screen
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Use the specified shaders
		glUseProgram(this->program_id);

		//Enable
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//Draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//Disable
		glDisableVertexAttribArray(0);
	}

	void Renderer::close()
	{
		glfwDestroyWindow(this->window);

		glfwTerminate();
	}
}
