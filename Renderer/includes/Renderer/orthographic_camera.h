#pragma once
#include <glm/glm.hpp>
#include "camera.h"
class OrthographicCamera : public Camera {
    public:
        OrthographicCamera(float x, float y, float width, float height);
        glm::mat4 getView();
        glm::mat4 getProjection();

    private:
    	float width, height;
};