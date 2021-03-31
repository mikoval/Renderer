#pragma once
#include <glm/glm.hpp>
#include "renderable.h"
class Rectangle: public Renderable {
    public:
        Rectangle(int width, int height);
        void render(Camera *camera);
    private:
        bool mInit;
        void init();
        unsigned int shaderProgram;
        unsigned int VAO;
};
