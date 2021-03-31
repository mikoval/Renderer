#pragma once
#include <glm/glm.hpp>
#include "renderable.h"
class Circle: public Renderable {
    public:
        Circle(int radius);
        void render(Camera *camera);
        glm::vec2 position;
        float rotation;
        glm::vec2 scale;
        void setShader(Shader *shader);
    private:
        bool mInit;
        void init();
        unsigned int shaderProgram;
        unsigned int VAO;
};
