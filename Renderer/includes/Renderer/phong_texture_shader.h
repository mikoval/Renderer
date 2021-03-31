#pragma once

#include <Renderer/shader.h>
#include <Renderer/color.h>
#include <Renderer/light.h>
#include <vector>

class PhongTextureShader: public Shader {
    public:
        PhongTextureShader(std::string ambient, std::string diffuse, std::string specular);
        void activate();
        void setLight(Light *light);
        int ambient;
        int diffuse;
        int specular;
        Camera *camera;
        void setLightList(std::vector<Light *> *lights);
    private:
        bool mInit;
        void init();
        float shiny;
        std::vector<Light *> *lights;

};
