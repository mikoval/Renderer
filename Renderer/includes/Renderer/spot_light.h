#pragma once
#include <glm/glm.hpp>
#include "light.h"
#include <Renderer/cube.h>

class SpotLight: public Light {
    public:
        SpotLight();
        void render(Camera *camera);
        glm::vec3 direction;
        char getLightType();
    private:
};
