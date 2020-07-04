#pragma once
#include <glm/glm.hpp>
#include "renderable.h"
class Circle: public Renderable {
    public:
        Circle(float radius);
        void render();
        glm::vec2 position;
    private:
        bool mInit;
        void init();
        unsigned int shaderProgram;
        unsigned int VAO;
};
