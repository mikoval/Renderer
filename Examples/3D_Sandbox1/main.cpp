#include <stdio.h>
#include <iostream>

#include <Renderer/renderer.h>
#include <Renderer/2d_shapes.h>
#include <Renderer/color_shader.h>
#include <Renderer/image_shader.h>
#include <Renderer/phong_color_shader.h>
#include <Renderer/light.h>
#include <Renderer/point_light.h>
#include <Renderer/cube.h>


using namespace std;

double mouseX = 0;
double mouseY = 0;

extern int screenWidth;
extern int screenHeight;

Renderable *renderable;
Light *light;

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

void update(double time) {
    //renderable->position.x = screenWidth/2.0 + 200.0 * sin(time);
    light->position.x =  5 * sin(time);
    light->position.z =  5 * cos(time);
    renderable->setOrientation(0.0, 1.0, 0.0, time*10.0);
}

int main() {
    Renderer *renderer;

    renderer = new Renderer(800, 800, "Hello world");

    renderer->setUpdateCallback(&update);

    vec3 position(0.0, 0.0, 20.0); 
    vec3 forward(0.0, 0.0,  -1.0); 
    vec3 up(0.0, 1.0, 0.0); 
    float aspect = 1;
    float fov = 45;
    Camera *camera = new PerspectiveCamera(position, forward, up, fov, aspect, 0.1, 40.0);
    renderer->setCamera(camera);

    renderer->setKeyboardCallback(&key_press);
    renderer->setMouseButtonCallback(&mouse_button_press);
    renderer->setMouseMoveCallback(&mouse_move);

/*
    ColorShader *colorShaderGreen = new ColorShader();
    colorShaderGreen->setColor(1.0, 1.0, 0.0, 1.0);

    ImageShader *imageShader = new ImageShader("assets/platformer/marble.jpg");
*/

    light = new PointLight();
    light->position.x = 0;
    light->position.y = 3;
    light->position.z = 0;
    light->setAmbient(0.2, 0.2, 0.2);
    light->setDiffuse(1.0, 1.0, 1.0);
    light->setSpecular(1.0, 1.0, 1.0);
    renderer->addLight(light);
    
    PhongColorShader *phong= new PhongColorShader();
    //phong->setLight(light);

    renderable = new Cube();
    renderable->position.x = 0;
    renderable->position.y = 0;
    renderable->position.z = 0;
    renderable->setShader(phong);
    //renderable->setShader(colorShaderGreen);
    renderer->addRenderable(renderable);

    renderer->start();

    return 0;
}
