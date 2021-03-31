#include <Renderer/point_light.h>
#include <iostream>
#include <Renderer/renderer.h>
#include <Renderer/color_shader.h>

#include <glm/gtc/matrix_transform.hpp>
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include <glm/gtx/quaternion.hpp>


#include "gl_utils.h"
#include "gl_core.h"

using namespace std;
PointLight::PointLight() {
    cube = new Cube();
    cube->scale.x = 1;
    cube->scale.y = 1;
    cube->scale.z = 1;
    mInit = false;
}

void PointLight::render(Camera *camera) {
    if(!mInit) {
        init();
    }
    cube->position = this->position;
    cube->render(camera);
}

void PointLight::init() {
    ColorShader *s =  new ColorShader();
    s->setColor(1.0, 1.0, 1.0, 1.0);
    cube->setShader(s);
    mInit = true;
}

char PointLight::getLightType() {
    return POINT_LIGHT;
}

