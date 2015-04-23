#include "stdio.h"
#include "stdlib.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "renderer.h"
#include "rendertypes.h"
#include "renderstructures.h"
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
		if ((this->window = glfwCreateWindow(400, 400, "Omnerra Test", NULL, NULL)))
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

		this->angle = 0.0f;

		//Initialise glbinding
		glbinding::Binding::initialize();

		RenderTypes::ObjectType cube =
		{
			8, {
				-10, -10, +10, 0.0f, 0.0f, 0.0f, //Vertex v0
				+10, -10, +10, 1.0f, 0.0f, 0.0f, //Vertex v1
				+10, -10, -10, 1.0f, 0.5f, 0.5f, //Vertex v2
				-10, -10, -10, 1.0f, 1.0f, 0.0f, //Vertex v3
				-10, +10, +10, 0.0f, 1.0f, 0.0f, //Vertex v4
				+10, +10, +10, 0.0f, 0.0f, 1.0f, //Vertex v5
				+10, +10, -10, 0.5f, 0.5f, 1.0f, //Vertex v6
				-10, +10, -10, 0.5f, 1.0f, 0.5f, //Vertex v7
			},
			12, {
				0, 1, 4, //Polygon 00
				1, 5, 4, //Polygon 01
				1, 2, 5, //Polygon 02
				2, 6, 5, //Polygon 03
				2, 3, 6, //Polygon 04
				3, 7, 6, //Polygon 05
				3, 0, 7, //Polygon 06
				0, 4, 7, //Polygon 07
				4, 5, 7, //Polygon 08
				5, 6, 7, //Polygon 09
				3, 2, 0, //Polygon 10
				2, 1, 0, //Polygon 11
			}
		};

		Structures::MeshObject* pyramid = new Structures::MeshObject();
		//pyramid->addVertex(new Structures::Vertex(0.0f, 0.0f, 1.0f), new Structures::Vertex(0.3f, 0.3f, 0.3f);
		//pyramid->addPolygon({-1.0f, +1.0f, -1.0f}, {+0.0f, +0.0f, +1.0f}, {+1.0f, +1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f});
		//pyramid->addPolygon({+1.0f, -1.0f, -1.0f}, {+0.0f, +0.0f, +1.0f}, {-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f});

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		//The vertex position array
		glGenVertexArrays(1, &this->vertex_array_id);
		glBindVertexArray(this->vertex_array_id);

		glGenBuffers(1, &this->vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer);

		//Pass the vertex position data to GL (the graphics card)
		glBufferData(GL_ARRAY_BUFFER, cube.getSize(), cube.getBuffer(), GL_STATIC_DRAW);
		//glBufferData(GL_ARRAY_BUFFER, pyramid->position_array->size(), pyramid->position_array, GL_STATIC_DRAW);

		//The vertex colour array
		glGenVertexArrays(1, &this->colour_array_id);
		glBindVertexArray(this->colour_array_id);

		glGenBuffers(1, &this->colour_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, this->colour_buffer);

		//Pass the vertex colour data to GL (the graphics card)
		glBufferData(GL_ARRAY_BUFFER, cube.getSize(), cube.vertex_colour_data, GL_STATIC_DRAW);



		//Load the shaders
		this->program_id = loadShaders( "shaders/simplevertexshader.glsl", "shaders/simplefragmentshader.glsl" );

		//Create the matrix
		this->matrix_id = glGetUniformLocation(this->program_id, "MVP");
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
		//Model space
		this->original_vector = glm::mat4(1.0f); //Model matrix
		this->original_vector = glm::scale(this->original_vector, glm::vec3(0.1f, 0.1f, 0.1f));
		this->original_vector = glm::rotate(this->original_vector, angle, glm::vec3(0.0f, 0.0f, 1.0f));
		this->original_vector = glm::rotate(this->original_vector, angle, glm::vec3(0.0f, 1.0f, 0.0f));
		this->original_vector = glm::rotate(this->original_vector, angle, glm::vec3(1.0f, 0.0f, 0.0f));
		this->original_vector = glm::translate(this->original_vector, glm::vec3(0.0f, 0.0f, 0.0f));

		//Camera space
		glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 4.0f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

		//Projection matrix
		glm::mat4 projection_matrix = glm::perspective(45.0f, 1.0f / 1.0f, 0.1f, 100.0f);
		this->original_vector = projection_matrix * view * this->original_vector;

		this->angle += 0.015f;

		//Clear the screen
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Use the specified shaders
		glUseProgram(this->program_id);

		//Enable
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, this->colour_buffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glUniformMatrix4fv(this->matrix_id, 1, GL_FALSE, &this->original_vector[0][0]);

		//Draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

		//Disable
		glDisableVertexAttribArray(0);
	}

	void Renderer::close()
	{
		glfwDestroyWindow(this->window);

		glfwTerminate();
	}
}
