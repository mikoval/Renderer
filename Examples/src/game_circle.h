#pragma once

#include "core.h"
#include "game_object.h"
class GameCircle: public GameObject {
    public:
        b2Body* body;
        GameCircle(int radius, int x, int y);
        void update();
        Renderable *getRenderable();
    private:
        Circle *renderable;

};
