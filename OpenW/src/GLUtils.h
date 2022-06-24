#pragma once

#define GL_ASSERT(x) if(!(x)) __debugbreak;


#ifdef _DEBUG
#define GLCall(x) GLClearError();\
	x;\
	GL_ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define GLCall(x) x
#endif

/// <summary>
/// Clears all the error occurred from the buffer
/// </summary>
void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);