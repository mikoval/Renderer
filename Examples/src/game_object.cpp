#include "game_object.h"

void GameObject::setType(b2BodyType type) {
    body -> SetType(type);
}

void GameObject::setTag(std::string tag) {
    this->tag = tag;
}

std::string GameObject::getTag() {
    return tag;
}

void GameObject::destroy() {
    toDestroy = true;
}
