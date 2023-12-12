#include <iostream>
#include <ostream>
#include <stdexcept>
#include "cam.h"
#include "utils/scenedata.h"


glm::mat4 ViewMatrix(glm::vec3 pos, glm::vec3 look, glm::vec3 up) {
    glm::vec3 posLocal = pos;
    glm::vec3 lookLocal = look;
    glm::vec3 upLocal = up;

    glm::vec4 tcol0(1, 0, 0, 0);
    glm::vec4 tcol1(0, 1, 0, 0);
    glm::vec4 tcol2(0, 0, 1, 0);
    glm::vec4 tcol3(-posLocal[0], -posLocal[1], -posLocal[2], 1);

    glm::mat4 translate(tcol0, tcol1, tcol2, tcol3);

    glm::vec3 w = -glm::normalize(lookLocal);
    glm::vec3 v = glm::normalize(upLocal - (glm::dot(upLocal, w) * w));
    glm::vec3 u = glm::cross(v, w);

    glm::mat4 rotate(u[0], v[0], w[0], 0, u[1], v[1], w[1], 0, u[2], v[2], w[2], 0, 0, 0, 0, 1);
    return rotate * translate;

    // Optional TODO: implement the getter or make your own design
    throw std::runtime_error("not implemented");
}

glm::mat4 inverseMat(glm::mat4 mat){
    return glm::inverse(mat);

}

glm::mat4 Cam::projectMatrixCalculator(){

    float c = -nearPlane/farPlane;
    float widthAngle = 2.0f * atan((tan(heightAngle/2)) * getAspectRatio()); // DOUBLE CHECK CALCULATIONS

    glm::vec4 tcol0(1/(farPlane * tan(widthAngle/2.f)), 0, 0, 0);
    glm::vec4 tcol1(0, 1/(farPlane * tan(heightAngle/2.f)), 0, 0);
    glm::vec4 tcol2(0, 0, 1/farPlane, 0);
    glm::vec4 tcol3(0, 0, 0, 1);

    glm::mat4 M1(tcol0, tcol1, tcol2, tcol3);

    glm::vec4 ucol0(1, 0, 0, 0);
    glm::vec4 ucol1(0, 1, 0, 0);
    glm::vec4 ucol2(0, 0, 1/(1 + c), -1);
    glm::vec4 ucol3(0, 0, -c/(1 + c), 0);


    glm::mat4 M2(ucol0, ucol1, ucol2, ucol3);

    glm::vec4 vcol0(1, 0, 0, 0);
    glm::vec4 vcol1(0, 1, 0, 0);
    glm::vec4 vcol2(0, 0, -2, 0);
    glm::vec4 vcol3(0, 0, -1, 1);


    glm::mat4 M3(vcol0, vcol1, vcol2, vcol3);
    return M3 * M2 * M1;

}

Cam::Cam(const SceneCameraData &cameraData, int width, int height, float nPlane, float fPlane/*, std::unordered_map<Qt::Key, bool> keyMapper*/) {
    Width = width;
    Height = height;
    pos = cameraData.pos;
    look = cameraData.look;
    up = cameraData.up;
    focalLength = cameraData.focalLength;
    aperture = cameraData.aperture;
    heightAngle = cameraData.heightAngle;
    viewMat = ViewMatrix(pos, look, up);
    invMat = inverseMat(viewMat);
    nearPlane = nPlane;
    farPlane = fPlane;
    projectMat = projectMatrixCalculator();
    //keyMap = keyMapper;


};

void Cam::updateCamNearPlane(float newNearPlane){
    nearPlane = newNearPlane;
    glm::mat4 newProj = projectMatrixCalculator();
    projectMat = newProj;

}

void Cam::updateCamFarPlane(float newFarPlane){
    farPlane = newFarPlane;
    glm::mat4 newProj = projectMatrixCalculator();
    projectMat = newProj;


}

void Cam::updateViewMatrix(glm::vec4 updatedPos,glm::vec4 updatedLook,glm::vec4 updatedUp){
    viewMat = ViewMatrix(updatedPos,look,up);

}

glm::mat4 Cam::getViewMatrix() const {
    return viewMat;
}

glm::mat4 Cam::getInverseViewMatrix() const {
    return invMat;
}
glm::mat4 Cam::getProjectMatrix() const {
    return projectMat;

}

void Cam::updateCameraLoc(glm::mat4 update){
    pos = update * pos;
}


float Cam::getAspectRatio() const {
    int n = Width;
    int d = Height;
    return (float) n/ (float) d;

    // Optional TODO: implement the getter or make your own design
    throw std::runtime_error("not implemented");
}

float Cam::getHeightAngle() const {
    // Optional TODO: implement the getter or make your own design
    return heightAngle;
    throw std::runtime_error("not implemented");
}

float Cam::getFocalLength() const {
    return focalLength;
    // Optional TODO: implement the getter or make your own design
    throw std::runtime_error("not implemented");
}

float Cam::getAperture() const {
    return aperture;
    throw std::runtime_error("not implemented");
}
