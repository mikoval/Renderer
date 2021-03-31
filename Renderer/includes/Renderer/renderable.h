#pragma once
#include <Renderer/color.h>
#include <Renderer/camera.h>
#include <Renderer/shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/common.hpp>
#include <string>

 class Renderable {
   public:
      Renderable();
      // pure virtual function
      virtual void render(Camera *camera) = 0;
      void setColor(float r, float g, float b, float a);
      void setImage(std::string path);
      Color color;
      void setUVTransform(glm::mat4 trans);
      void setOrientation(float x, float y, float z, float angle);
      void setShader(Shader *shader);
      void setTransforms(Camera *camera);
      glm::vec3 position;
      glm::quat orientation;
      glm::vec3 scale;


    private:
    protected:
	  unsigned int texture = 0;
          Shader *shader;
	  glm::mat4 UVTransform = glm::mat4(1.0);
};
