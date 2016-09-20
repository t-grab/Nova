#ifndef NOVA_CAMERA_H
#define NOVA_CAMERA_H

#include "std.h"

namespace Nova {
    class Camera {
        glm::vec3 m_position;
        glm::vec3 m_direction;
        glm::vec3 m_up;

        glm::mat4 m_model;

    public:
        Camera();
        Camera(const glm::vec3& pos, const glm::vec3& dir, const glm::vec3& up);

        void look_at(const glm::vec3& pos, const glm::vec3& dir, const glm::vec3& up);
        void move();
        void rotate();
    };
}

#endif