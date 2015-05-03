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
#include "structures/model.h"
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
		if ((this->window = glfwCreateWindow(640, 480, "Omnerra Test", NULL, NULL)))
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
				-0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 0.0f, //Vertex v0
				+0.5f, -0.5f, +0.5f, 1.0f, 0.0f, 0.0f, //Vertex v1
				+0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.5f, //Vertex v2
				-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, //Vertex v3
				-0.5f, +0.5f, +0.5f, 0.0f, 1.0f, 0.0f, //Vertex v4
				+0.5f, +0.5f, +0.5f, 0.0f, 0.0f, 1.0f, //Vertex v5
				+0.5f, +0.5f, -0.5f, 0.5f, 0.5f, 1.0f, //Vertex v6
				-0.5f, +0.5f, -0.5f, 0.5f, 1.0f, 0.5f, //Vertex v7
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

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		//The vertex position array
		glGenVertexArrays(1, &this->vertex_array_id);
		glBindVertexArray(this->vertex_array_id);

		glGenBuffers(1, &this->vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer);

		Render::Mesh* mesh = new Render::Mesh();
		mesh->loadOBJ("Skeleton.obj");
		this->colour_array_id = mesh->polygon.size();

		//Pass the vertex position data to GL (the graphics card)
		glBufferData(GL_ARRAY_BUFFER, mesh->getBufferSize(), &mesh->polygon[0], GL_STATIC_DRAW);

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
		this->angle += 0.015f;

		//Clear the screen
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Use the specified shaders
		glUseProgram(this->program_id);

		glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer);

		//Enable
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 11, (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 11, (void*)(sizeof(GLfloat) * 8));

		for (int x = 0; x < 1; x ++)
		{
			for (int y = 0; y < 1; y ++)
			{
				for (int z = 0; z < 1; z ++)
				{
					//Model space
					this->original_vector = glm::mat4(1.0f); //Model matrix
					this->original_vector = glm::rotate(this->original_vector, angle, glm::vec3(0.0f, 0.0f, 1.0f));
					//this->original_vector = glm::rotate(this->original_vector, angle, glm::vec3(0.0f, 1.0f, 0.0f));
					//this->original_vector = glm::rotate(this->original_vector, angle, glm::vec3(1.0f, 0.0f, 0.0f));
					this->original_vector = glm::rotate(this->original_vector, 1.55f, glm::vec3(1.0f, 0.0f, 0.0f));
					this->original_vector = glm::translate(this->original_vector, glm::vec3((float)x * 2, (float)y * 2, (float)z * 2));
					this->original_vector = glm::scale(this->original_vector, glm::vec3(0.4f, 0.4f, 0.4f));
					//this->original_vector = glm::rotate(this->original_vector, angle, glm::vec3(1.0f, 0.0f, 0.0f));

					//Camera space
					glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 2.0f, 1.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

					//Projection matrix
					glm::mat4 projection_matrix = glm::perspective(1.5f, 640.0f / 480.0f, 0.01f, 1000.0f);
					this->original_vector = projection_matrix * view * this->original_vector;

					glUniformMatrix4fv(this->matrix_id, 1, GL_FALSE, &this->original_vector[0][0]);

					//Draw the triangle
					//if (abs(x) + abs(y) + abs(z) < 12)
					glDrawArrays(GL_TRIANGLES, 0, this->colour_array_id * 3);
				}
			}
	}

		//Disable
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}

	void Renderer::close()
	{
		glfwDestroyWindow(this->window);

		glfwTerminate();
	}
}
