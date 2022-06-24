#include "GLUtils.h"
#include "GL/glew.h"
#include <iostream>

void GLClearError()
{
	while (glGetError());
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL error] ( " << error << " ) " << function <<
			" " << file << " : " << (int)line << std::endl;
		return false;
	}

	return true;
}
