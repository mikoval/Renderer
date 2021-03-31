#pragma once

#include <Renderer/shader.h>
#include <Renderer/color.h>
#include <Renderer/light.h>
#include <vector>


class PhongColorShader: public Shader {
    public:
        PhongColorShader();
        void activate();
        void setLightList(std::vector<Light *> *lights);
        Color ambient;
        Color diffuse;
        Color specular;
        Camera *camera;

    private:
        bool mInit;
        void init();
        float shiny;

        std::vector<Light *> *lights;
};
