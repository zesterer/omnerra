#ifndef LOADSHADER_H
#define LOADSHADER_H

#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

using namespace gl;

namespace Omnerra
{
	GLuint loadShaders(const char * vertex_file_path,const char * fragment_file_path);
}

#endif
