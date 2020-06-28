#pragma once
#include<GL/glew.h>

#include"VertexArray.h"
#include"IndexBuffer.h"
#include"Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearErorr();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__));

void GLClearErorr();
bool GLLogCall(const char* function, const char* file, unsigned int line);

class Renderer
{

public:
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

};