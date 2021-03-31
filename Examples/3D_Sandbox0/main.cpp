#include <stdio.h>
#include <iostream>

#include <Renderer/renderer.h>
#include <Renderer/2d_shapes.h>
#include <Renderer/color_shader.h>
#include <Renderer/image_shader.h>
#include <Renderer/phong_color_shader.h>
#include <Renderer/phong_texture_shader.h>
#include <Renderer/light.h>
#include <Renderer/point_light.h>
#include <Renderer/directional_light.h>
#include <Renderer/spot_light.h>
#include <Renderer/cube.h>
#include <glm/gtx/string_cast.hpp>


using namespace std;

double mLastX = 0;
double mLastY = 0;
bool mFirstMouse = true;
double mYaw   = -90.0f;
double mPitch =  0.0f;

extern int screenWidth;
extern int screenHeight;

Renderer *renderer;
float RIGHT_PRESSED, LEFT_PRESSED, UP_PRESSED, BACK_PRESSED;

Renderable *renderable;
PerspectiveCamera *camera;
Light *pointLight;
DirectionalLight *directionalLight;
SpotLight *spotLight;

void mouse_button_press(int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    }
}

void mouse_move(double x, double y)
{
    if (mFirstMouse)
    {
        mLastX = x;
        mLastY = y;
        mFirstMouse = false;
    }
  
    float xoffset = x - mLastX;
    float yoffset = mLastY - y; 
    mLastX = x;
    mLastY = y;

    float mSensitivity = 0.1f;
    xoffset *= mSensitivity;
    yoffset *= mSensitivity;

    mYaw   += xoffset;
    mPitch += yoffset;

    if(mPitch > 89.0f)
        mPitch = 89.0f;
    if(mPitch < -89.0f)
        mPitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    direction.y = sin(glm::radians(mPitch));
    direction.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    camera->front = glm::normalize(direction);
}

void key_press(int key, int scancode, int action, int mods) {
    //cout << "Key pressed: " << key << ", Action: " << action << endl;
    if(action) {
        action = 1;
    }
    if(key == 65) {
        RIGHT_PRESSED = action;
    }
    if(key == 68) {
        LEFT_PRESSED = action;
    }
    if(key == 83) {
        UP_PRESSED = action;
    }
    if(key == 87) {
        BACK_PRESSED = action;
    }
    if(key == 256) {
        renderer->kill();
    }
}

void update(double time) {
/*
    light->position.x =  10 * sin(time);
    light->position.z =  10 * cos(time);
*/

    float velocity = 0.1;
    glm::vec3 right = glm::normalize(glm::cross(camera->front, camera->up));
    camera->position += (LEFT_PRESSED - RIGHT_PRESSED) * right  * velocity;
    camera->position += (BACK_PRESSED - UP_PRESSED) * camera->front * velocity;
}

int main() {
    renderer = new Renderer(800, 800, "Hello world");
    RIGHT_PRESSED = LEFT_PRESSED = UP_PRESSED = BACK_PRESSED = 0;

    renderer->setUpdateCallback(&update);

    vec3 position(0.0, 5.0, 10.0); 
    vec3 forward(0.0, 0.0,  -1.0); 
    vec3 up(0.0, 1.0, 0.0); 
    float aspect = 1;
    float fov = 45;
    camera = new PerspectiveCamera(position, forward, up, fov, aspect, 0.1, 40.0);
    renderer->setCamera(camera);

    renderer->setKeyboardCallback(&key_press);
    renderer->setMouseButtonCallback(&mouse_button_press);
    renderer->setMouseMoveCallback(&mouse_move);


    ColorShader *colorShaderGreen = new ColorShader();
    colorShaderGreen->setColor(1.0, 1.0, 0.0, 1.0);

    ImageShader *imageShader = new ImageShader("assets/platformer/marble.jpg");


    pointLight = new PointLight();
    pointLight->position.x = 0;
    pointLight->position.y = 5;
    pointLight->position.z = -10;
    
    pointLight->setAmbient(0.2, 0.2, 0.2);
    pointLight->setDiffuse(1.0, 1.0, 1.0);
    pointLight->setSpecular(1.0, 1.0, 1.0);
    renderer->addLight(pointLight);

    directionalLight = new DirectionalLight();
    directionalLight->setAmbient(0.2, 0.2, 0.2);
    directionalLight->setDiffuse(1.0, 1.0, 1.0);
    directionalLight->setSpecular(1.0, 1.0, 1.0);
    directionalLight->setDirection(0.0, -1.0, 0.0);
    renderer->addLight(directionalLight);

    //renderer->addLight(spotLight);
    
/*
    PhongColorShader *phong= new PhongColorShader();
    phong->setLightList(renderer->getLightList());
    phong->ambient.r = 1.0; phong->ambient.g = 0.0; phong->ambient.b = 0.0;
    phong->diffuse.r = 1.0; phong->diffuse.g = 0.0; phong->diffuse.b = 0.0;
    phong->specular.r = 1.0; phong->specular.g = 1.0; phong->specular.b = 1.0;
    phong->camera = camera;
*/
    PhongTextureShader *phong= new PhongTextureShader("assets/3D/box/diffuse.png", "assets/3D/box/diffuse.png", "assets/3D/box/specular.png");
    phong->setLightList(renderer->getLightList());
    phong->camera = camera;

    renderable = new Cube();
    renderable->position.x = 0;
    renderable->position.y = 0;
    renderable->position.z = 0;
    renderable->setShader(phong);
    //renderable->setShader(imageShader);
    //renderable->setShader(colorShaderGreen);
    renderer->addRenderable(renderable);

    renderer->start();

    return 0;
}
