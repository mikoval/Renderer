#pragma once
#include <glm/glm.hpp>
#include "renderable.h"

#define POINT_LIGHT 0
#define SPOT_LIGHT 1
#define DIRECTIONAL_LIGHT 2

class Light: public Renderable {
    public:
        Color ambient;
        Color diffuse;
        Color specular;
        void setAmbient(float r, float g, float b);
        void setDiffuse(float r, float g, float b);
        void setSpecular(float r, float g, float b);
        virtual char getLightType() = 0;

    private:
};
