#pragma once

#include <Renderer/color.h>
#include <Renderer/shader.h>

class ColorShader: public Shader {
    public:
        ColorShader();
        ColorShader(float r, float g, float b, float a);
        ColorShader(Color color);
        void setColor(float r, float g, float b, float a);
        void setColor(Color color);
        void activate();
    private:
        Color color;
        bool mInit;
        void init();
        
};
