#pragma once

#include "core.h"
class GameObject {
    public:
        b2Body* body; 
        b2Fixture* fixture; 
        virtual void update() = 0;
        virtual Renderable *getRenderable() = 0;
        void setType(b2BodyType type) ;
    private:

};
