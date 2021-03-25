#include <Renderer/orthographic_camera.h>
#include <iostream>
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include "gl_core.h"

OrthographicCamera::OrthographicCamera(float x, float y, float width, float height) {
    position.x = x;
    position.y = y;
    this->width = width;
    this->height = height;

}


glm::mat4 OrthographicCamera::getView() { 
    return glm::ortho(position.x - width/2, position.x + width/2, position.y - height/2, position.y + height/2, -1.0f, 100.0f);
}
glm::mat4 OrthographicCamera::getProjection() { 
    return glm::mat4(1.0); 
}

 
