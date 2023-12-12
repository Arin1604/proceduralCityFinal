#pragma once

#include "qnamespace.h"
#include "utils/scenedata.h"
#include <glm/glm.hpp>
#include <unordered_map>

// My camera class from raytracer modified to account for projection matrix

class Cam {
public:
    // Returns the view matrix for the current camera settings.
    // You might also want to define another function that return the inverse of the view matrix.
    Cam(const SceneCameraData &cameraData, int width, int height, float np, float fp/*, std::unordered_map<Qt::Key, bool> keyMap*/);
    glm::mat4 getViewMatrix() const;
    glm::mat4 getInverseViewMatrix() const;
    glm::mat4 getProjectMatrix() const;
    float Width;
    float Height;
    glm::vec4 pos;
    glm::vec4 look;
    glm::vec4 up;
    float heightAngle; // The height angle of the camera in RADIANS

    float aperture;    // Only applicable for depth of field
    float focalLength;
    glm::mat4 viewMat;
    glm::mat4 invMat;
    glm::mat4 projectMat;
    glm::mat4 projectMatrixCalculator();
    void updateViewMatrix(glm::vec4 updatedPos,glm::vec4 updatedLook,glm::vec4 updatedUp);


    float nearPlane;
    float farPlane;

    std::unordered_map<Qt::Key, bool> keyMap;

    void updateCamNearPlane(float newNearPlane);
    void updateCamFarPlane(float newFarPlane);

    // Returns the aspect ratio of the camera.
    float getAspectRatio() const;

    // Returns the height angle of the camera in RADIANS.
    float getHeightAngle() const;

    // Returns the focal length of this camera.
    // This is for the depth of field extra-credit feature only;
    // You can ignore if you are not attempting to implement depth of field.
    float getFocalLength() const;

    // Returns the focal length of this camera.
    // This is for the depth of field extra-credit feature only;
    // You can ignore if you are not attempting to implement depth of field.
    float getAperture() const;

    void updateCameraLoc(glm::mat4 update);
};
