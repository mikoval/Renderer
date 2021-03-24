#pragma once
#include <glm/glm.hpp>
class Camera {
    public:
        void render();
        virtual glm::mat4 getView() = 0;
        virtual glm::mat4 getProjection() = 0;
        glm::vec3 position;


    private:
        glm::vec3 front;
        glm::vec3 up;
};