#pragma once

#include "core.h"
#include "game_object.h"
class GameCircle: public GameObject {
    public:
        Circle *renderable;
        b2Body* body;
        GameCircle(int radius, int x, int y);
        void update();
    private:

};
