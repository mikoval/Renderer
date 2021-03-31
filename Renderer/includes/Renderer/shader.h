#pragma once
#include <glm/glm.hpp>
#include <string>

class Shader {
    public:
        virtual void activate() = 0;
        int getProgram(); 
    protected:
        int shaderProgram;
};
