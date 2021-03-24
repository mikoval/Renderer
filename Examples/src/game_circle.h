#pragma once

#include "core.h"
#include "game_object.h"
class GameCircle: public GameObject {
    public:
        GameCircle(int radius, int x, int y);
        void update();
        Renderable *getRenderable();
        void setFriction(float friction);
        void setRestitution(float restitution);
    private:
        Circle *renderable;


};
