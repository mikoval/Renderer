#pragma once

#include "core.h"
#include "game_object.h"
class GameRect : public GameObject {
    public:
        Rectangle *renderable;
        b2Body* body;
        GameRect(int width, int height, int x, int y);
        void update();
    private:

};
