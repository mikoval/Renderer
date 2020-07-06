#pragma once
#include <glm/glm.hpp>
#include "renderable.h"
class Rectangle: public Renderable {
    public:
        Rectangle(int width, int height);
        void render();
        glm::vec2 position;
        float rotation;
        glm::vec2 scale;
    private:
        bool mInit;
        void init();
        unsigned int shaderProgram;
        unsigned int VAO;
};
