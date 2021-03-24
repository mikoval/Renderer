#pragma once
#include <glm/glm.hpp>
#include "renderable.h"
class Circle: public Renderable {
    public:
        Circle(int radius);
        void render(glm::mat4 mat);
        glm::vec2 position;
        float rotation;
        glm::vec2 scale;
    private:
        bool mInit;
        void init();
        unsigned int shaderProgram;
        unsigned int VAO;
};
