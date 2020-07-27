//g++ -o hellot main.cpp -lglfw -lGL -lGLEW 
#include <glad/glad.h>
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <iostream>
#include <thread>

#include <Renderer/renderer.h>
#include <Renderer/circle.h>
#include "gl_context.h"
#include "gl_core.h"

using namespace std;

thread *t1;

GLFWwindow* window;
static void (*key_callback)(int, int, int, int);
static void (*mouse_button_callback)(int, int, int);
static void (*mouse_move_callback)(double, double);
static void (*update_callback)(unsigned long);

int screenWidth;
int screenHeight;


void key_press_base(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key_callback)  {
        key_callback(key, scancode, action, mods);
    }
}

void mouse_press_base(GLFWwindow* window, int button,  int action, int mods)
{
    if(mouse_button_callback)  {
        mouse_button_callback(button, action, mods);
    }
}

void mouse_move_base(GLFWwindow* window,  double x, double y)
{
    if(mouse_move_callback)  {
        mouse_move_callback(x,y);
    }
}

void Renderer::setKeyboardCallback(void (*callback)(int, int, int, int)) {
    key_callback = callback;
}

void Renderer::setMouseButtonCallback(void (*callback)(int, int, int)) {
    mouse_button_callback = callback;
}

void Renderer::setMouseMoveCallback(void (*callback)(double, double)) {
    mouse_move_callback = callback;
}

void Renderer::setUpdateCallback(void (*callback)(unsigned long)) {
    update_callback = callback;
}

void Renderer::setBackgroundColor(float r, float g, float b, float a) {
    backgroundColor = new Color(r, g, b, a);
}


Renderer::Renderer(int width, int height, string name) {
    this->width = width;
    this->height = height;
    this->name = name;
    screenWidth = width;
    screenHeight = height;

    window = makeWindow(width, height, name);

    //t1 = new thread(renderLoop, this, width, height, name);
}

void Renderer::start() {
    renderLoop(this, width, height, name);
}


template<typename T>
inline void remove(vector<T> & v, const T & item)
{
    v.erase(std::remove(v.begin(), v.end(), item), v.end());
}

void Renderer::removeRenderable(Renderable *renderable) {
    remove(renderable_list, renderable);
}

void Renderer::addRenderable(Renderable *renderable) {
    renderable_list.push_back(renderable);
}

vector<Renderable *>  Renderer::getRenderableList() {
    return renderable_list;
    
}

int renderLoop(Renderer *renderer, int width, int height, string name) {
    glfwSetKeyCallback(window, key_press_base);
    glfwSetMouseButtonCallback(window, mouse_press_base);
    glfwSetCursorPosCallback(window, mouse_move_base);

    while(!glfwWindowShouldClose(window)) {
        if(renderer->backgroundColor) {
            Color *color = renderer->backgroundColor;
            glClearColor(color->r, color->g, color->b, 1.0);
        } else {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        }
        glClear(GL_COLOR_BUFFER_BIT);

        vector<Renderable *> renderableList = renderer->getRenderableList();
        for(int i = 0; i < renderableList.size(); i++) {
           renderableList[i]->render(); 
        }
        glfwPollEvents();
        glfwSwapBuffers(window);
        update_callback(0);
    }

    // close GL context and any other GLFW resources
    glfwTerminate();
    return 0;
}
