#pragma once

#include <Renderer/shader.h>

class ImageShader: public Shader {
    public:
        ImageShader(std::string path);
        void activate();
    private:
        int image;
        bool mInit;
        void init();
        int texture;        
};
