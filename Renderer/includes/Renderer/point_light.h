#pragma once
#include <glm/glm.hpp>
#include "light.h"
#include <Renderer/cube.h>

class PointLight: public Light {
    public:
        PointLight();
        void render(Camera *camera);
        char getLightType();
    private:
        bool mInit;
        void init();
        unsigned int shaderProgram;
        unsigned int VAO;
        Cube *cube;
};
