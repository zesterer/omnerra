#include "iostream"

#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

#include "rendertypes.h"

using namespace gl;

namespace Omnerra
{
	namespace RenderTypes
	{
		GLfloat* ObjectType::getBuffer()
		{
			for (int count = 0; count < this->polygon_count; count ++)
			{
				//The position data
				this->vertex_buffer_data[count * 2 * 3 * 3 +  0] = this->vertex[this->polygon[count].a].x;
				this->vertex_buffer_data[count * 2 * 3 * 3 +  1] = this->vertex[this->polygon[count].a].y;
				this->vertex_buffer_data[count * 2 * 3 * 3 +  2] = this->vertex[this->polygon[count].a].z;

				//The colour data
				this->vertex_buffer_data[count * 2 * 3 * 3 +  3] = this->vertex[this->polygon[count].a].r;
				this->vertex_buffer_data[count * 2 * 3 * 3 +  4] = this->vertex[this->polygon[count].a].g;
				this->vertex_buffer_data[count * 2 * 3 * 3 +  5] = this->vertex[this->polygon[count].a].b;

				this->vertex_buffer_data[count * 2 * 3 * 3 +  6] = this->vertex[this->polygon[count].b].x;
				this->vertex_buffer_data[count * 2 * 3 * 3 +  7] = this->vertex[this->polygon[count].b].y;
				this->vertex_buffer_data[count * 2 * 3 * 3 +  8] = this->vertex[this->polygon[count].b].z;

				this->vertex_buffer_data[count * 2 * 3 * 3 +  9] = this->vertex[this->polygon[count].b].r;
				this->vertex_buffer_data[count * 2 * 3 * 3 + 10] = this->vertex[this->polygon[count].b].g;
				this->vertex_buffer_data[count * 2 * 3 * 3 + 11] = this->vertex[this->polygon[count].b].b;

				this->vertex_buffer_data[count * 2 * 3 * 3 + 12] = this->vertex[this->polygon[count].c].x;
				this->vertex_buffer_data[count * 2 * 3 * 3 + 13] = this->vertex[this->polygon[count].c].y;
				this->vertex_buffer_data[count * 2 * 3 * 3 + 14] = this->vertex[this->polygon[count].c].z;

				this->vertex_buffer_data[count * 2 * 3 * 3 + 15] = this->vertex[this->polygon[count].c].r;
				this->vertex_buffer_data[count * 2 * 3 * 3 + 16] = this->vertex[this->polygon[count].c].g;
				this->vertex_buffer_data[count * 2 * 3 * 3 + 17] = this->vertex[this->polygon[count].c].b;
			}

			return this->vertex_buffer_data;
		}

		int ObjectType::getSize()
		{
			return sizeof(GLfloat) * this->polygon_count * 3 * 3;
		}
	}
}
