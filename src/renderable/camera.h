#ifndef CAMERA_H
#define CAMERA_H

#include "utils/GLIncludes.h"

#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
   enum class Movement;
public:
   Camera();
   Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);

   glm::mat4 getViewMatrix() const;
   void processKeyboard(Movement camMov, float deltaTime);
   void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
   void processMouseScroll(float yoffset);
private:
   void updateCameraVectors();
private:
   /* Camera Attributes */
   glm::vec3 Position;
   glm::vec3 Front;
   glm::vec3 Up;
   glm::vec3 Right;
   glm::vec3 WorldUp;
   /* Euler Angles */
   float Yaw;
   float Pitch;
   /* Camera options */
   float MovementSpeed;
   float MouseSensitivity;
   float Zoom;
public:
   enum class Movement
   {
      FORWARD,
      BACKWARD,
      LEFT,
      RIGHT
   };
};

#endif
