#pragma once
#include <glm/glm.hpp>
#include "camera.h"
class OrthographicCamera : public Camera {
    public:
        OrthographicCamera(float x, float y, float width, float height, float near, float far);
        glm::mat4 getView();
        glm::mat4 getProjection();

    private:
    	float width, height, near, far;
};
