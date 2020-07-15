#include "game_object.h"

void GameObject::setType(b2BodyType type) {
    body -> SetType(type);
}
