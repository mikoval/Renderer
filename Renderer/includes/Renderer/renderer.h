#pragma once

#include <string>
#include <Renderer/color.h>
#include <vector>
#include <Renderer/renderable.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h> // GLFW helper library
#include <glm/glm.hpp>

class Renderer {
    public:
        Renderer(int width, int height, std::string name);
        void setKeyboardCallback(void (*cb)(int, int, int, int));
        void setMouseButtonCallback(void (*cb)(int, int, int));
        void setMouseMoveCallback(void (*cb)(double, double));
        void setUpdateCallback(void (*callback)(unsigned long));
        void setBackgroundColor(float r, float g, float b, float a);
        Color *backgroundColor = nullptr;
        void addRenderable(Renderable *renderable);
        std::vector<Renderable *> getRenderableList();
        void start();
    private:
        std::vector<Renderable *> renderable_list;
        int width;
        int height;
        std::string name;
};

