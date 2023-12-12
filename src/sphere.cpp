#include "sphere.h"

void sphere::updateParams(int param1, int param2) {
    m_vertexData = std::vector<float>();
    m_param1 = param1;
    m_param2 = param2;
    setVertexData();
}

void sphere::makeTile(glm::vec3 topLeft,
                      glm::vec3 topRight,
                      glm::vec3 bottomLeft,
                      glm::vec3 bottomRight) {
    // Task 5: Implement the makeTile() function for a sphere
    // Note: this function is very similar to the makeTile() function for Cube,
    //       but the normals are calculated in a different way!

    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, glm::normalize(topLeft));

    insertVec3(m_vertexData, bottomLeft);
    insertVec3(m_vertexData, glm::normalize(bottomLeft));

    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, glm::normalize(bottomRight));
    //

    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, glm::normalize(bottomRight));

    insertVec3(m_vertexData, topRight);
    insertVec3(m_vertexData, glm::normalize(topRight));

    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, glm::normalize(topLeft));
}

void sphere::makeWedge(float currentTheta, float nextTheta) {
    // Task 6: create a single wedge of the sphere using the
    //         makeTile() function you implemented in Task 5
    // Note: think about how param 1 comes into play here!
    float phiStep = glm::radians(180.f / /*15.f*/m_param1);
    for (int i = 0; i <  /*15.f*/m_param1; i++){
        float x1 = 0.5f * sin(i * phiStep) * sin(currentTheta);
        float y1 = 0.5f * cos(i * phiStep);
        float z1 = 0.5f * sin(i * phiStep) * cos(currentTheta);
        glm::vec3 topLeft(x1, y1, z1);

        float x2 = 0.5f * sin(i * phiStep) * sin(nextTheta);
        float y2 = 0.5f * cos(i * phiStep);
        float z2 = 0.5f * sin(i * phiStep) * cos(nextTheta);
        glm::vec3 topRight(x2, y2, z2);

        float x3 = 0.5f * sin((i+1) * phiStep) * sin(currentTheta);
        float y3 = 0.5f * cos((i+1) * phiStep);
        float z3 = 0.5f * sin((i+1) * phiStep) * cos(currentTheta);
        glm::vec3 bottomLeft(x3, y3, z3);

        float x4 = 0.5f * sin((i+1) * phiStep) * sin(nextTheta);
        float y4 = 0.5f * cos((i+1) * phiStep);
        float z4 = 0.5f * sin((i+1) * phiStep) * cos(nextTheta);
        glm::vec3 bottomRight(x4, y4, z4);

        makeTile(topLeft, topRight, bottomLeft, bottomRight);
    }



}

void sphere::makeSphere() {
    // Task 7: create a full sphere using the makeWedge() function you
    //         implemented in Task 6
    // Note: think about how param 2 comes into play here!
    float thetaStep = glm::radians(360.f / m_param2);

    for(int i = 0; i < /*15.f*/m_param2; i++){
        makeWedge(i * thetaStep, (i + 1) * thetaStep);
    }


}

void sphere::setVertexData() {
    // Uncomment these lines to make a wedge for Task 6, then comment them out for Task 7:

    //     float thetaStep = glm::radians(360.f / m_param2);
    //     float currentTheta = 0 * thetaStep;
    //     float nextTheta = 1 * thetaStep;
    //     makeWedge(currentTheta, nextTheta);

    // Uncomment these lines to make sphere for Task 7:

    makeSphere();
}

// Inserts a glm::vec3 into a vector of floats.
// This will come in handy if you want to take advantage of vectors to build your shape!
void sphere::insertVec3(std::vector<float> &data, glm::vec3 v) {
    data.push_back(v.x);
    data.push_back(v.y);
    data.push_back(v.z);
}
