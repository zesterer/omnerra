#ifndef RENDERTYPES_H
#define RENDERTYPES_H

#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

#define MAX_VERTICES 2000
#define MAX_POLYGONS 2000

using namespace gl;

namespace Omnerra
{
	namespace RenderTypes
	{
		struct VertexType
		{
			GLfloat x, y, z;
			GLfloat r, g, b;
		};

		struct PolygonType
		{
			int a, b, c;
		};

		struct ObjectType
		{
			public: int vertex_count;
			public: VertexType vertex[MAX_VERTICES];
			public: int polygon_count;
			public: PolygonType polygon[MAX_POLYGONS];

			public: GLfloat vertex_buffer_data[MAX_POLYGONS * 3 * 3];
			public: GLfloat vertex_colour_data[MAX_POLYGONS * 3 * 3];

			public: GLfloat* getBuffer();
			public: int getSize();
		};
	}
}

#endif
