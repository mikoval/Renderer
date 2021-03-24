#pragma once

#include "core.h"
#include "game_object.h"
class GameRect : public GameObject {
    public:
        Rectangle *renderable;
        GameRect(int width, int height, int x, int y);
        void update();
        Renderable *getRenderable();
        void setFriction(float friction);
        void setRestitution(float restitution);
    private:

};
