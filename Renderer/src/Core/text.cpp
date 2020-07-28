#include <Renderer/text.h>
#include <iostream>
#include <map>

#include <glm/gtc/matrix_transform.hpp>
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

#include "gl_utils.h"
#include "gl_core.h"

#include <algorithm>
#include <ft2build.h>
#include FT_FREETYPE_H

using namespace std;

#define PADDING 30
#define ATLAS_SIZE 128

int n;

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    long Advance;    // Offset to advance to next glyph
};

struct character_info {
  float ax; // advance.x
  float ay; // advance.y
  
  float bw; // bitmap.width;
  float bh; // bitmap.rows;
  
  float bl; // bitmap_left;
  float bt; // bitmap_top;
  
  float tx; // x offset of glyph in texture coordinates
} c[128];

std::map<char, Character> Characters;


 GLuint texture;
 int atlas_width;
 int atlas_height;

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
    FT_Set_Pixel_Sizes(face, 0, ATLAS_SIZE);

    FT_GlyphSlot g = face->glyph;
    unsigned int w = 0;
    unsigned int h = 0;

    for(int i = 32; i < 128; i++) {
      if(FT_Load_Char(face, i, FT_LOAD_RENDER)) {
        fprintf(stderr, "Loading character %c failed!\n", i);
        continue;
      }

      w += g->bitmap.width + PADDING;
      h = std::max(h, g->bitmap.rows);
    }

    /* you might as well save this value as it is needed later on */
     atlas_width = w;
     atlas_height = h;


    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    const unsigned char data[] = {0xFF, 0, 0, 0xFF};


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    int x = 0;

    for(int i = 32; i < 128; i++) {
        if(FT_Load_Char(face, i, FT_LOAD_RENDER))
            continue;
        c[i].ax = g->advance.x >> 6;
        c[i].ay = g->advance.y >> 6;

        c[i].bw = g->bitmap.width;
        c[i].bh = g->bitmap.rows;

        c[i].bl = g->bitmap_left;
        c[i].bt = g->bitmap_top;

        c[i].tx = (float)x / w;

        glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, g->bitmap.width, g->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);

      x += g->bitmap.width + PADDING;
    }
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





    glUseProgram(shaderProgram);


    glBindVertexArray(VAO);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    glUniform4f(glGetUniformLocation(shaderProgram, "textColor"), color.r, color.g, color.b, color.a);

    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(shaderProgram, "text"), 0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glm::mat4 P = glm::ortho(0.0f, (float)screenWidth,0.0f,(float)screenHeight, -1.0f, 100.0f);
    glm::mat4 model = glm::mat4(1.0);
    /*
    model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
    model = glm::rotate(model, rotation, glm::vec3(0.0, 0.0, 1.0));
    model = glm::scale(model, glm::vec3(scale.x, scale.y, 0.0));
    */
    model = P * model;

    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
    unsigned int colorLoc = glGetUniformLocation(shaderProgram, "color");
    glUniform4f(colorLoc, color.r, color.g, color.b, color.a);
  
    glDrawArrays(GL_TRIANGLES, 0, n);
}

void Text::setText(string text) {
    this->text = text;
        glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    struct point {
        GLfloat x;
        GLfloat y;
        GLfloat s;
        GLfloat t;
      } coords[6 * strlen(text.c_str())];

      n = 0;

  float x = position.x;
  float y = position.y;
  float sx = scale.x / ATLAS_SIZE;
  float sy = scale.y / ATLAS_SIZE;
  for(const char *p = text.c_str(); *p; p++) { 
    float x2 =  x + c[*p].bl * sx;
    float y2 = -y - c[*p].bt * sy;
    float w = c[*p].bw * sx;
    float h = c[*p].bh * sy;

    /* Advance the cursor to the start of the next character */
    x += c[*p].ax * sx;
    y += c[*p].ay * sy;

    /* Skip glyphs that have no pixels */
    if(!w || !h)
      continue;

    coords[n++] = (point){x2,     -y2    , c[*p].tx,                                            0};
    coords[n++] = (point){x2 + w, -y2    , c[*p].tx + c[*p].bw / atlas_width,   0};
    coords[n++] = (point){x2,     -y2 - h, c[*p].tx,                                          c[*p].bh / atlas_height}; //remember: each glyph occupies a different amount of vertical space
    coords[n++] = (point){x2 + w, -y2    , c[*p].tx + c[*p].bw / atlas_width,   0};
    coords[n++] = (point){x2,     -y2 - h, c[*p].tx,                                          c[*p].bh / atlas_height};
    coords[n++] = (point){x2 + w, -y2 - h, c[*p].tx + c[*p].bw / atlas_width,                 c[*p].bh / atlas_height};
  }

  glBufferData(GL_ARRAY_BUFFER, sizeof coords, coords, GL_DYNAMIC_DRAW);

      glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

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
//            "FragColor = vec4(texture(text, TexCoords).r, 0.0, 1.0, 1.0f);\n"
        "}\n\0";


    shaderProgram = buildShaderProgram(vertexShaderSource, fragmentShaderSource);



    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    setText(text);

    mInit = true;

}
