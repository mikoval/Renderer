//g++ -o hellot main.cpp -lglfw -lGL -lGLEW 
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <iostream>
#include <thread>

#include <Renderer/renderer.h>
#include <Renderer/circle.h>
#include "gl_context.h"

using namespace std;

thread *t1;

GLFWwindow* window;
static void (*key_callback)(int, int, int, int);


void key_press_base(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key_callback)  {
        key_callback(key, scancode, action, mods);
    }
}

void Renderer::setKeyboardCallback(void (*foo)(int, int, int, int)) {
    key_callback = foo;
}

void Renderer::setBackgroundColor(float r, float g, float b, float a) {
    backgroundColor = new Color(r, g, b, a);
}


Renderer::Renderer(int width, int height, string name) {
    t1 = new thread(renderLoop, this, width, height, name);
}

void Renderer::addRenderable(Renderable *renderable) {
    renderable_list.push_back(renderable);
}

vector<Renderable *>  Renderer::getRenderableList() {
    return renderable_list;
    
}

int renderLoop(Renderer *renderer, int width, int height, string name) {
    window = makeWindow(width, height, name);
    glfwSetKeyCallback(window, key_press_base);

    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        vector<Renderable *> renderableList = renderer->getRenderableList();
        for(int i = 0; i < renderableList.size(); i++) {
           renderableList[i]->render(); 
        }
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // close GL context and any other GLFW resources
    glfwTerminate();
    return 0;
}
