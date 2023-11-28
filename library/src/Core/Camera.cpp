#include <Core/Camera.hpp>

Camera::Camera()
{
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(position, position + front, up);
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime)
{
    const float velocity = movementSpeed * deltaTime;
    if (direction == CameraMovement::Forward)
    {
        position += front * velocity;
    }
    if (direction == CameraMovement::Backward)
    {
        position -= front * velocity;
    }
    if (direction == CameraMovement::Left)
    {
        position -= right * velocity;
    }
    if (direction == CameraMovement::Right)
    {
        position += right * velocity;
    }
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (pitch > 89.0f)
        {
            pitch = 89.0f;
        }
        if (pitch < -89.0f)
        {
            pitch = -89.0f;
        }
    }

    updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset)
{
    zoom -= yoffset;
    if (zoom < 1.0f)
    {
        zoom = 1.0f;
    }
    if (zoom > 45.0f)
    {
        zoom = 45.0f;
    }
}

void Camera::updateCameraVectors()
{
    const glm::vec3 cameraFront(
        cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
        sin(glm::radians(pitch)),
        sin(glm::radians(yaw)) * cos(glm::radians(pitch))
    );

    front = glm::normalize(cameraFront);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
