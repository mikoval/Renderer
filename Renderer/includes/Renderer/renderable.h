#pragma once
#include <Renderer/color.h>
#include <glm/glm.hpp>
#include <string>

 class Renderable {
   public:
      // pure virtual function
      virtual void render(glm::mat4 mat) = 0;
      void setColor(float r, float g, float b, float a);
      void setImage(std::string path);
      Color color;
      void setUVTransform(glm::mat4 trans);

    private:
    protected:
	  unsigned int texture = 0;
	  glm::mat4 UVTransform = glm::mat4(1.0);


};