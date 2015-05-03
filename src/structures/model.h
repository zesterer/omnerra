#ifndef STRUCTURES_MODEL_H
#define STRUCTURES_MODEL_H

#include "string"
#include "vector"

#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

using namespace std;

using namespace gl;

namespace Omnerra
{
	namespace Render
  	{
		struct VertexPos
	  	{
			GLfloat x, y, z;
		};

	  	struct VertexCol
	  	{
			GLfloat r, g, b;
		};

	  	struct VertexTex
	  	{
			GLfloat x, y;
		};

	  	struct VertexNorm
	  	{
			GLfloat i, j, k;
		};

	  	struct Vertex
	  	{
			VertexPos pos;
			VertexCol col;
			VertexTex tex;
			VertexNorm norm;
		};

	  	struct Polygon
	  	{
			Vertex a, b, c;
		};

	  	struct Mesh
	  	{
			public: vector<Polygon> polygon;
			public: vector<GLfloat> buffer;

			public: bool loadOBJ(const char* obj_path);
			public: GLuint getBufferSize();
			public: void reBuffer();
		};
	}
}

#endif
