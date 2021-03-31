#pragma once
#include <glm/glm.hpp>
#include "light.h"
#include <Renderer/cube.h>

class DirectionalLight: public Light {
    public:
        DirectionalLight();
        void render(Camera *camera);
        glm::vec3 direction;
        void setDirection(float x, float  y, float z);
        char getLightType();
    private:
};
