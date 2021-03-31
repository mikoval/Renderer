#include <Renderer/ImageLoader.h>
#include <Renderer/image_shader.h>
#include <iostream>
#include <Renderer/renderer.h>
#include "stb_image.h"
#include <map>

using namespace std;

static std::map<std::string, int> texture_map;

int loadImage(std::string path) {
    GLuint texture;
    if (texture_map.count(path)){
        texture  = texture_map[path];
    } else {
        int width =0 , height=0, nrChannels=0;
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        printf("LOADING TEXTURE WITH ---- width : %d, height : %d , channels : %d \n", width, height, nrChannels);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        
        // load and generate the texture
        if (data)
        {
            unsigned int channel_type;
            if(nrChannels == 3) { channel_type = GL_RGB; }
            else if(nrChannels == 4) { channel_type = GL_RGBA; }
            else { assert(0); }
            glTexImage2D(GL_TEXTURE_2D, 0, channel_type, width, height, 0, channel_type, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            std::cout << "SUCCESSFULLY LOADED texture" << std::endl;

        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
        texture = texture;
        texture_map[path] = texture;
    }
    return texture;
}
