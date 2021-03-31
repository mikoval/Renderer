#include <Renderer/perspective_camera.h>
#include <iostream>
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include "gl_core.h"

PerspectiveCamera::PerspectiveCamera(vec3 position, vec3 front, vec3 up, float fov, float aspect, float near, float far) {
    this->position = position;
    this->front = front;
    this->up = up;
    this->fov = fov;
    this->aspect = aspect;
    this->near = near;
    this->far = far;
}


glm::mat4 PerspectiveCamera::getView() { 
    return glm::lookAt(position, position + front, up);
}

void PerspectiveCamera::lookAt(glm::vec3 target) { 
    front = glm::normalize(target - position);
}

glm::mat4 PerspectiveCamera::getProjection() { 
    return glm::perspective(fov, aspect, near, far); 
}
