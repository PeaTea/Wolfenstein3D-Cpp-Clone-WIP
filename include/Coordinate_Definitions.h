#ifndef COORD_DEF_H
#define COORD_DEF_H

#include <GL/glew.h>

namespace COORD_DEFS
{
	GLfloat vertices[] =
	{
		 0.5f,	0.5f, 0.0f,		1.0f, 1.0f,
		-0.5f,	0.5f, 0.0f,		0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f
	};

	GLint indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};
}


#endif