#pragma once
#include <glm/glm.hpp>
#include "renderable.h"
class Triangle: public Renderable {
    public:
        Triangle(glm::vec2 a, glm::vec2 b, glm::vec2 c);
        void render(glm::mat4 mat);
        glm::vec2 position;
        float rotation;
        float scale;
    private:
        bool mInit;
        void init();
        unsigned int shaderProgram;
        unsigned int VAO;
        glm::vec2 a;
        glm::vec2 b;
        glm::vec2 c;
};
