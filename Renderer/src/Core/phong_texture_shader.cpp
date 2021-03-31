#include <Renderer/phong_texture_shader.h>
#include <Renderer/file.h>
#include <iostream>
#include <Renderer/renderer.h>
#include <Renderer/ImageLoader.h>
#include "stb_image.h"

#include <glm/gtc/matrix_transform.hpp>
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

#include "gl_utils.h"
#include "gl_core.h"
#include <map>


using namespace std;

static std::map<std::string, int> texture_map;

PhongTextureShader::PhongTextureShader(std::string ambient, std::string diffuse, std::string specular){
    this->ambient=loadImage(ambient);
    this->diffuse=loadImage(diffuse);
    this->specular=loadImage(specular);
}



void PhongTextureShader::setLightList(std::vector<Light *> *lights){
    this->lights = lights;
}

void PhongTextureShader::activate() {
    if(!mInit) {
        init();
    } 

    glUseProgram(shaderProgram);

    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(shaderProgram, "material.ambient"), 0);
    glBindTexture(GL_TEXTURE_2D, ambient);

    glActiveTexture(GL_TEXTURE1);
    glUniform1i(glGetUniformLocation(shaderProgram, "material.diffuse"), 1);
    glBindTexture(GL_TEXTURE_2D, diffuse);

    glActiveTexture(GL_TEXTURE2);
    glUniform1i(glGetUniformLocation(shaderProgram, "material.specular"), 2);
    glBindTexture(GL_TEXTURE_2D, specular);

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

void PhongTextureShader::init(){
    mInit = true;
    const char *vertexShaderSource = ReadFile((char *)"assets/shaders/PhongTextureShader/shader.vert");
    const char *fragmentShaderSource = ReadFile((char *)"assets/shaders/PhongTextureShader/shader.frag");

    shaderProgram = buildShaderProgram(vertexShaderSource, fragmentShaderSource);
}
