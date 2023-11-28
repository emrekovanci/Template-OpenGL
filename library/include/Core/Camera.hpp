#pragma once

#include <glm/gtc/matrix_transform.hpp>

enum class CameraMovement
{
    Forward,
    Backward,
    Left,
    Right
};

class Camera
{
public:
    // Camera Attributes
    glm::vec3 position { 0.0f, 0.0f, 3.0f };
    glm::vec3 up { 0.0f, 1.0f, 0.0f };
    glm::vec3 front { 0.0f, 0.0f, -1.0f };
    glm::vec3 right { 1.0f, 0.0f, 0.0f };
    glm::vec3 worldUp { 0.0f, 1.0f, 0.0f };

    // Euler Angles
    float yaw { -90.0f };
    float pitch { 0.0f };

    // Camera Options
    float movementSpeed { 2.5f };
    float mouseSensitivity { 0.1f };
    float zoom { 45.0f };

    Camera();

    glm::mat4 getViewMatrix() const;

    void processKeyboard(CameraMovement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void processMouseScroll(float yoffset);

private:
    void updateCameraVectors();
};
