#pragma once

#include "core.h"
class GameObject {
    public:
        Renderable *renderable;
        b2Body* body;
        virtual void update() = 0;
    private:

};
