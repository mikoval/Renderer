#include <Renderer/directional_light.h>
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
DirectionalLight::DirectionalLight() {
}

void DirectionalLight::render(Camera *camera) {
}

void DirectionalLight::setDirection(float x, float y, float z) {
    this->direction = glm::vec3(x, y, z);
}

char DirectionalLight::getLightType() {
    return DIRECTIONAL_LIGHT;
}

