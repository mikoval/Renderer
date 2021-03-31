#include <Renderer/spot_light.h>
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
SpotLight::SpotLight() {
}

void SpotLight::render(Camera *camera) {
}

char SpotLight::getLightType() {
    return SPOT_LIGHT;
}

