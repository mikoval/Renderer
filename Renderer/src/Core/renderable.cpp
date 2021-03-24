#include <Renderer/renderable.h>
#include <stdio.h>
#include "stb_image.h"
#include "gl_core.h"
#include <iostream>

#include <map>
    
static std::map<std::string, int> texture_map;


void Renderable::setColor(float r, float g, float b, float a) {
    color.r=r;
    color.g=g;
    color.b=b;
    color.a=a;
}

void Renderable::setImage(std::string path){
	if (texture_map.count(path)){
		printf("FINDME: LOADING SAVED iMAGE : %s  \n ", path.c_str());
		this->texture = texture_map[path];
	} else {
		unsigned int texture;
		printf("FINDME: LOADING iMAGE : %s  \n ", path.c_str());
	    int width =0 , height=0, nrChannels=0;
		unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0); 
		printf("FINDME: %d %d %d \n", width, height, nrChannels);
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
		    std::cout << "LINE : " << __LINE__ << " ERROR: " << glGetError() << std::endl;
		printf("FINDME: TeXTURE ID : %d \n", texture);
		this->texture = texture;
		texture_map[path] = texture;
	}
}
void Renderable::setUVTransform(glm::mat4 trans){
	this->UVTransform = trans;
}