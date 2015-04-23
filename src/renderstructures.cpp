#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

#include "renderstructures.h"

using namespace gl;

namespace Omnerra
{
	namespace Structures
	{
		public: void init()
		{
			glGenVertexArrays(1, &this->vao_id);
			glGenBuffers(1, &this->vbo_vertices_id);
			glGenBuffers(1, &this->vbo_colours_id);
			glGenBuffers(1, &this->vbo_indices_id);
		}

		public: void buffer()
		{
			glBindVertexArray(this->vao_id);

			glBindBuffer(GL_ARRAY_BUFFER, this->vbo_vertices_id);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->vertex_array.size(), (GLfloat*)&this->vertex_array[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, this->vbo_colours_id);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->colour_array.size(), (GLfloat*)&this->colour_array[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vbo_indices_id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat) * this->indices_array.size(), (GLfloat*)&this->indices_array[0], GL_STATIC_DRAW);

			glBindVertexArray(0);
		}

		public: void MeshObject::addVertex(Vertex vertex, Colour colour)
		{
			this->vertex_array.push_back(vertex);
			this->colour_array.push_back(colour);
		}

		public: void MeshObject::addPolygon(Vertex a, Vertex b, Vertex c, Colour col_a, Colour col_b, Colour col_c)
		{
			this->addVertex(a, col_a);
			this->addVertex(b, col_b);
			this->addVertex(c, col_c);
		}
	}
}
