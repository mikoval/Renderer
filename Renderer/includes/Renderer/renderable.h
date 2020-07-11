#pragma once

 class Renderable {
   public:
      // pure virtual function
      virtual void render() = 0;
      void setColor(float r, float g, float b, float a);
      float r, g, b, a;
};
