#ifndef _TEXTURED_QUAD_INCLUDE
#define _TEXTURED_QUAD_INCLUDE


#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"


class TexturedQuad
{

	//FJA.sn
	TexturedQuad(glm::vec2 geom[2], glm::vec2 texCoords[2], ShaderProgram& program);
	//FJA.en

public:
	// Textured quads can only be created inside an OpenGL context
	static TexturedQuad *createTexturedQuad(glm::vec2 geom[2], glm::vec2 texCoords[2], ShaderProgram &program);

	//FJA.so
	//TexturedQuad(glm::vec2 geom[2], glm::vec2 texCoords[2], ShaderProgram &program);
	//FJA.eo

	void render(const Texture &tex) const;
	void free();

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;

};


#endif // _TEXTURED_QUAD_INCLUDE

