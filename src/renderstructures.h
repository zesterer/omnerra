#ifndef RENDERSTRUCTURES_H
#define RENDERSTRUCTURES_H

#include "vector"

#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

#define MAX_VERTICES 2000
#define MAX_POLYGONS 2000

using namespace std;

using namespace gl;

namespace Omnerra
{
	namespace Structures
  	{
		struct Vertex
		{
			GLfloat x, y, z;
		};

		struct Polygon
		{
			GLuint a, b, c;
		};

		struct Colour
		{
			GLfloat r, g, b;
		};

		struct MeshObject
		{
			public: vector<Vertex> vertex_array;
			public: vector<Colour> colour_array;
			public: vector<Polygon> polygon_array;

			public: GLuint vao_id;
			public: GLuint vbo_vertices_id;
			public: GLuint vbo_colours_id;
			public: GLuint vbo_indices_id;

			public: void init();

			public: void addVertex(Vertex vertex, Colour colour);
			public: void addPolygon(GLuint a, GLuint b, GLuint c);
		};
	}
}

#endif
