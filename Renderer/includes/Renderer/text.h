#pragma once
#include <string>
#include "renderable.h"
#include <glm/glm.hpp>

typedef int Font;


Font LoadFont(std::string path);

class Text: public Renderable {
public:
	Text(std::string text, Font font, float x, float y, float size);
	void setText(std::string text);
	void setSize(int size);
	void render();
    glm::vec2 position;
    float rotation = 0.0;
    glm::vec2 scale;
private:
	bool mInit;
	void init();
	std::string text;
	Font font;
	unsigned int shaderProgram;
	unsigned int VAO;
	unsigned int VBO;
};