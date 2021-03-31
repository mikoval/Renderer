#include <Renderer/light.h>
#include <iostream>
#include <Renderer/renderer.h>

#include <glm/gtc/matrix_transform.hpp>
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include <glm/gtx/quaternion.hpp>


#include "gl_utils.h"
#include "gl_core.h"

using namespace std;

void Light::setAmbient(float r, float g, float b) {
    ambient.r = r;
    ambient.g = g;
    ambient.b = b;
}
void Light::setDiffuse(float r, float g, float b) {
    diffuse.r = r;
    diffuse.g = g;
    diffuse.b = b;
}
void Light::setSpecular(float r, float g, float b) {
    specular.r = r;
    specular.g = g;
    specular.b = b;
}
