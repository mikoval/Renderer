
using namespace std;

#include <Renderer/renderer.h>
#include <Renderer/2d_shapes.h>
#include <iostream>  

Renderer *renderer;

void test(int key, int scancode, int action, int mods) {
    cout << "Key pressed: " << key << endl;
    if(key == 65) {
        renderer->setBackgroundColor(1, 0, 0, 0);
    }
    if(key == 68) {
        renderer->setBackgroundColor(0, 1, 0, 0);
    }
    if(key == 83) {
        renderer->setBackgroundColor(0, 0, 1, 0);
    }
}

int main() {
    renderer = new Renderer(1200, 800, "Hello world");

    renderer->setKeyboardCallback(&test);

    Triangle *triangle = new Triangle(glm::vec2(-0.5, -0.5), glm::vec2(-0.2, 0.5), glm::vec2(0.1, 0.7) );
    Triangle *triangle2 = new Triangle(glm::vec2(0.5, -0.5), glm::vec2(0.2, -0.7), glm::vec2(0.0, -0.9) );

    renderer->addRenderable(triangle);
    renderer->addRenderable(triangle2);
    while(true);
    return 0;
}

