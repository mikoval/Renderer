#include <Renderer/phong_color_shader.h>
#include <Renderer/file.h>
#include <iostream>
#include <Renderer/renderer.h>
#include "stb_image.h"

#include <glm/gtc/matrix_transform.hpp>
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

#include "gl_utils.h"
#include "gl_core.h"
#include <map>


using namespace std;

static std::map<std::string, int> texture_map;

PhongColorShader::PhongColorShader() {
    ambient.r = 0.0; ambient.g = 0.0; ambient.b = 0.0;
    diffuse.r = 1.0; diffuse.g = 1.0; diffuse.b = 1.0;
    specular.r = 1.0; specular.g = 1.0; specular.b = 1.0;
 }


void PhongColorShader::setLightList(std::vector<Light *> *lights){
    this->lights = lights;
}
void PhongColorShader::activate() {
    if(!mInit) {
        init();
    } 

    glUseProgram(shaderProgram);


    glUniform3f(glGetUniformLocation(shaderProgram, "material.ambient"),ambient.r, ambient.g, ambient.b);
    glUniform3f(glGetUniformLocation(shaderProgram, "material.diffuse"),diffuse.r, diffuse.g, diffuse.b);
    glUniform3f(glGetUniformLocation(shaderProgram, "material.specular"),specular.r, specular.g, specular.b);
    glUniform1f(glGetUniformLocation(shaderProgram, "material.shininess"),32.f);


    for(int i = 0; i < lights->size(); i++ ) {
        Light *light = (*lights)[i];
        char type = light->getLightType();
        if(type == POINT_LIGHT) {
            Color lightAmbient = light->ambient;
            Color lightDiffuse = light->diffuse;
            Color lightSpecular = light->specular;
            glm::vec3 lightPosition = light->position;
            glUniform3f(glGetUniformLocation(shaderProgram, "light.ambient"),lightAmbient.r, lightAmbient.g, lightAmbient.b);
            glUniform3f(glGetUniformLocation(shaderProgram, "light.diffuse"),lightDiffuse.r, lightDiffuse.g, lightDiffuse.b);
            glUniform3f(glGetUniformLocation(shaderProgram, "light.specular"),lightSpecular.r, lightSpecular.g, lightSpecular.b );
            glUniform3f(glGetUniformLocation(shaderProgram, "light.position"),lightPosition.x, lightPosition.y, lightPosition.z);
        }
    }

    glUniform3f(glGetUniformLocation(shaderProgram, "viewPos"),camera->position.x, camera->position.y, camera->position.z);
}

void PhongColorShader::init(){
    mInit = true;
    char *vertexShaderSource = ReadFile((char *)"assets/shaders/PhongColorShader/shader.vert");
    char *fragmentShaderSource = ReadFile((char *)"assets/shaders/PhongColorShader/shader.frag");
    shaderProgram = buildShaderProgram(vertexShaderSource, fragmentShaderSource);
}
