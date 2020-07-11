#include <Renderer/renderable.h>
#include <stdio.h>
void Renderable::setColor(float r, float g, float b, float a) {
    printf("calling set color \n");
    this->r= r;
    this->g= g;
    this->b= b;
    this->a= a;
}

