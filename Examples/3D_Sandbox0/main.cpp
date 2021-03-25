#include <stdio.h>
#include <iostream>

#include <Renderer/renderer.h>

using namespace std;

double mouseX = 0;
double mouseY = 0;

extern int screenWidth;
extern int screenHeight;

void mouse_button_press(int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    }
}

void mouse_move(double x, double y)
{
    mouseX = x;
    mouseY = screenHeight-y;
}

void key_press(int key, int scancode, int action, int mods) {
    cout << "Key pressed: " << key << endl;
    if(key == 65) {
    }
    if(key == 68) {
    }
    if(key == 83) {
    }
    if(key == 70) {
    }
}

void update(unsigned long time) {
}

int main() {
    Renderer *renderer;

    renderer = new Renderer(1200, 800, "Hello world");

    renderer->setUpdateCallback(&update);

    Camera *camera = new OrthographicCamera(screenWidth/2, screenHeight/2, screenWidth, screenHeight);
    renderer->setCamera(camera);

    renderer->setKeyboardCallback(&key_press);
    renderer->setMouseButtonCallback(&mouse_button_press);
    renderer->setMouseMoveCallback(&mouse_move);

    renderer->start();

    printf("HELLO WORLD\n");
    return 0;
}
