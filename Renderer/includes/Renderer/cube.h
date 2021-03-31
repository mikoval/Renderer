#pragma once
#include <glm/glm.hpp>
#include "renderable.h"
class Cube: public Renderable {
    public:
        Cube();
        void render(Camera *camera);
    private:
        bool mInit;
        void init();
        unsigned int shaderProgram;
        unsigned int VAO;
};
