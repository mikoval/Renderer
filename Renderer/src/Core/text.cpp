#include <Renderer/text.h>
#include <iostream>
#include <map>

#include <glm/gtc/matrix_transform.hpp>
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

#include "gl_utils.h"
#include "gl_core.h"

#include <ft2build.h>
#include FT_FREETYPE_H

using namespace std;


struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    long Advance;    // Offset to advance to next glyph
};

std::map<char, Character> Characters;



Font LoadFont(string path) {
    cout << "LOADING : " << path << endl;

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return -1;
    }

    FT_Face face;
    if (FT_New_Face(ft, path.c_str(), 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return -1;
    } else {
        std::cout << "LOADED FONT" << std::endl;
    }
    FT_Set_Pixel_Sizes(face, 0, 48);


    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
      
    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture, 
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    return 0;

}

Text::Text(std::string text, Font font, float x, float y, float size){
    mInit = false;
    std::cout << "CREATING TEXT: " << text << std::endl;
    this->text = text;
    this->font = font;
    this->position.x = x;
    this->position.y = y;
    this->scale.x = size;
    this->scale.y = size;
}

void Text::render() {
    if(!mInit) {
        init();
    }


unsigned int VAO, VBO;
glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
glBindVertexArray(VAO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
glEnableVertexAttribArray(0);
glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindVertexArray(0);  



    glm::mat4 P = glm::ortho(0.0f, (float)screenWidth,0.0f,(float)screenHeight, -1.0f, 100.0f);


    glm::mat4 model = glm::mat4(1.0);
    /*
    model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
    model = glm::rotate(model, rotation, glm::vec3(0.0, 0.0, 1.0));
    model = glm::scale(model, glm::vec3(scale.x, scale.y, 0.0));
    */
    model = P * model;
    

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    glUseProgram(shaderProgram);

    glUniform4f(glGetUniformLocation(shaderProgram, "textColor"), color.r, color.g, color.b, color.a);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
    unsigned int colorLoc = glGetUniformLocation(shaderProgram, "color");
    glUniform4f(colorLoc, color.r, color.g, color.b, color.a);

    // iterate through all characters
    std::string::const_iterator c;
    float x = position.x;
    float y = position.y;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale.x;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale.y;

        float w = ch.Size.x * scale.x;
        float h = ch.Size.y * scale.y;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },            
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }           
        };
        std::cout << "X : " << xpos << ", Y : " << ypos + h << std::endl;
        std::cout << "X2 : " << xpos << ", Y2 : " << ypos << std::endl;
        std::cout << "X3 : " << xpos + w << ", Y3 : " << ypos << std::endl;
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale.x; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    /*
    glBindVertexArray(VAO);

    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");

    unsigned int colorLoc = glGetUniformLocation(shaderProgram, "color");
    glUniform4f(colorLoc, color.r, color.g, color.b, color.a);

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    */

}

void Text::init() {
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>\n"
        "out vec2 TexCoords;\n"
        "uniform mat4 transform;"
        "void main()\n"
        "{\n"
        "   gl_Position =  transform * vec4(vertex.xy, 0.0, 1.0);\n"
        "   TexCoords = vertex.zw;\n"
        "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
        "in vec2 TexCoords;\n"
        "out vec4 FragColor;\n"
        "uniform vec4 color;\n"
        "uniform sampler2D text;\n"
        "void main()\n"
        "{\n"
            "vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);\n"
//            "vec4 sampled = vec4(1.0, 1.0, 1.0, 1.0);\n"
            "FragColor = color * sampled;\n"
//            "FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n\0";


    shaderProgram = buildShaderProgram(vertexShaderSource, fragmentShaderSource);


    mInit = true;

}
