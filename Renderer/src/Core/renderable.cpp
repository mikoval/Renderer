#include <Renderer/renderable.h>
#include <stdio.h>
#include "stb_image.h"
#include "gl_core.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include <glm/gtx/quaternion.hpp>


#include <map>
    
static std::map<std::string, int> texture_map;

Renderable::Renderable() {
    position.x = 0;
    position.y = 0;
    position.z = 0;
    scale.x = 1;
    scale.y = 1;
    scale.z = 1;
    orientation.x = 1;
    orientation.y = 0;
    orientation.z = 0;
    orientation.w = 0;
}

void Renderable::setColor(float r, float g, float b, float a) {
    color.r=r;
    color.g=g;
    color.b=b;
    color.a=a;
}

void Renderable::setImage(std::string path){
	if (texture_map.count(path)){
		this->texture = texture_map[path];
	} else {
		unsigned int texture;
	    int width =0 , height=0, nrChannels=0;
		unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0); 
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// load and generate the texture
		if (data)
		{
		    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		    glGenerateMipmap(GL_TEXTURE_2D);
		   	std::cout << "SUCCESSFULLY LOADED texture" << std::endl;

		}
		else
		{
		    std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
		this->texture = texture;
		texture_map[path] = texture;
	}
}
void Renderable::setUVTransform(glm::mat4 trans){
	this->UVTransform = trans;
}

void Renderable::setOrientation(float x, float y, float z, float angle) {
    orientation = glm::angleAxis(glm::radians(angle), glm::vec3(x, y, z));
}

void Renderable::setShader(Shader *shader) {
    this->shader = shader;
}

void Renderable::setTransforms(Camera *camera) {
    shader->activate();

    //std::cout << "POSITON : " << glm::to_string(position) << std::endl;
    //std::cout << "ORIENTATION : " << glm::to_string(orientation) << std::endl;
    //std::cout << "SCALE : " << glm::to_string(scale) << std::endl;
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
    model = model * glm::toMat4(orientation);
    model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));

    unsigned int modelLoc = glGetUniformLocation(shader->getProgram(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    unsigned int viewLoc = glGetUniformLocation(shader->getProgram(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->getView()));

    unsigned int projLoc = glGetUniformLocation(shader->getProgram(), "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera->getProjection()));

    //unsigned int uv_transformLoc = glGetUniformLocation(shader->getProgram(), "uv_transform");
    //glUniformMatrix4fv(uv_transformLoc, 1, GL_FALSE, glm::value_ptr(UVTransform));
}
