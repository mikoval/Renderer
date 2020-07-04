#pragma once

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <glm/glm.hpp>
#include <string>
#include <Renderer/color.h>
#include <vector>
#include <Renderer/renderable.h>

class Renderer {
    public:
        Renderer(int width, int height, std::string name);
        void setKeyboardCallback(void (*foo)(int, int, int, int));
        void setBackgroundColor(float r, float g, float b, float a);
        Color *backgroundColor;
        void addRenderable(Renderable *renderable);
        std::vector<Renderable *> getRenderableList();
    private:
        std::vector<Renderable *> renderable_list;
};

