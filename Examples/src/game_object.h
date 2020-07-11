#pragma once

#include "core.h"
class GameObject {
    public:
        virtual void update() = 0;
        virtual Renderable *getRenderable() = 0;
    private:

};
