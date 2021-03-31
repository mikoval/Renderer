#pragma once
#include <glm/glm.hpp>
#include "camera.h"
using namespace glm;
class PerspectiveCamera : public Camera {
    public:
        PerspectiveCamera(vec3 position, vec3 forward, vec3 up, float fov, float aspect, float near, float far);
        glm::mat4 getView();
        glm::mat4 getProjection();
        void lookAt(glm::vec3 target);

    private:
        float fov, aspect, near, far;
};
