#pragma once
#include <Renderer/color.h>
 class Renderable {
   public:
      // pure virtual function
      virtual void render() = 0;
      void setColor(float r, float g, float b, float a);
      Color color;
};
