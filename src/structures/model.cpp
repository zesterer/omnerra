#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "model.h"

using namespace std;

namespace Omnerra
{
	namespace Render
	{
		bool Mesh::loadOBJ(const char* obj_path)
		{
			//Clear the polygon list ready for the new mesh
			this->polygon.clear();

			vector<VertexPos> tmp_pos;
			vector<VertexTex> tmp_tex;
			vector<VertexNorm> tmp_norm;

			//Open the file
			FILE* file = fopen(obj_path, "r");
			if (file == NULL)
			{
				printf("Unable to open OBJ file '%s'.\n", obj_path);
				return false;
			}

			//Keep reading the file until we get to the end
			while (true)
			{
				char line_header[128];

				//Find the first word of the line
				int res = fscanf(file, "%s", line_header);

				if (res == EOF) //We got to the end of the file
					break;

				//Parse the line
				if (strcmp(line_header, "v") == 0) //Deal with the vertex positions
				{
					VertexPos pos;
					fscanf(file, "%f %f %f\n", &pos.x, &pos.y, &pos.z);
					tmp_pos.push_back(pos);
				}
				else if (strcmp(line_header, "vt") == 0) //Deal with the vertex UV coordinates
				{
					VertexTex tex;
					fscanf(file, "%f %f\n", &tex.x, &tex.y);
					tmp_tex.push_back(tex);
				}
				else if (strcmp(line_header, "vn") == 0) //Deal with the vertex UV coordinates
				{
					VertexNorm norm;
					fscanf(file, "%f %f %f\n", &norm.i, &norm.j, &norm.k);
					tmp_norm.push_back(norm);
				}
				else if (strcmp(line_header, "f") == 0) //Deal with the vertex UV coordinates
				{
					string vertex1, vertex2, vertex3;
					unsigned int pos_index[3], tex_index[3], norm_index[3];

					int matches = 0;

					matches = fscanf(file, "%d/%d %d/%d %d/%d\n", &pos_index[0], &tex_index[0], &pos_index[1], &tex_index[1], &pos_index[2], &tex_index[2]);

					if (matches != 6)
					{
						matches = -3 + fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &pos_index[0], &tex_index[0], &norm_index[0], &pos_index[1], &tex_index[1], &norm_index[1], &pos_index[2], &tex_index[2], &norm_index[2]);
					}

					if (matches != 6)
					{
						printf("Unable to parse OBJ file '%s'.\n", obj_path);
						return false;
					}

					Polygon poly;

					//Find the parts of the polygon
					poly.a.pos = tmp_pos[pos_index[0] - 1];
					poly.b.pos = tmp_pos[pos_index[1] - 1];
					poly.c.pos = tmp_pos[pos_index[2] - 1];

					poly.a.tex = tmp_tex[tex_index[0] - 1];
					poly.b.tex = tmp_tex[tex_index[1] - 1];
					poly.c.tex = tmp_tex[tex_index[2] - 1];

					if (matches == 9)
					{
						poly.a.norm = tmp_norm[norm_index[0]];
						poly.b.norm = tmp_norm[norm_index[1]];
						poly.c.norm = tmp_norm[norm_index[2]];
					}

					this->polygon.push_back(poly);
				}
			}

			return false;
		}

		GLuint Mesh::getBufferSize()
		{
			return this->polygon.size() * sizeof(Polygon);
		}

		void Mesh::reBuffer()
		{

		}
	}
}
