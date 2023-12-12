#include "cylinder.h"

void cylinder::updateParams(int param1, int param2) {
    m_vertexData = std::vector<float>();
    m_param1 = param1;
    m_param2 = param2;
    setVertexData();
}

void cylinder::makeTile(glm::vec3 top,
                        glm::vec3 topRight,
                        glm::vec3 bottomLeft,
                        glm::vec3 bottomRight) {
    // Task 5: Implement the makeTile() function for a Sphere
    // Note: this function is very similar to the makeTile() function for Cube,
    //       but the normals are calculated in a different way!

    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * bottomRight[0], 0.0, 2.0 * bottomRight[2])));

    insertVec3(m_vertexData, bottomLeft);
    insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * bottomLeft[0], 0.0, 2.0 * bottomLeft[2])));

    insertVec3(m_vertexData, top);
    insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * top[0], 0.0, 2.0 * top[2])));



    insertVec3(m_vertexData, top);
    insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * top[0], 0.0, 2.0 * top[2])));

    insertVec3(m_vertexData, topRight);
    insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * topRight[0], 0.0, 2.0 * topRight[2])));


    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * bottomRight[0], 0.0, 2.0 * bottomRight[2])));
    //


}

void cylinder::makeBase(glm::vec3 top,
                           glm::vec3 topRight,
                           glm::vec3 bottomLeft,
                           glm::vec3 bottomRight){


    insertVec3(m_vertexData, top);
    insertVec3(m_vertexData, glm::normalize(glm::vec3(0, top[1], 0)));
    insertVec3(m_vertexData, bottomLeft);
    insertVec3(m_vertexData, glm::normalize(glm::vec3(0, bottomLeft[1], 0)));
    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, glm::normalize(glm::vec3(0, bottomRight[1], 0)));

    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, glm::normalize(glm::vec3(0, bottomRight[1], 0)));
    insertVec3(m_vertexData, topRight);
    insertVec3(m_vertexData, glm::normalize(glm::vec3(0, topRight[1], 0)));
    insertVec3(m_vertexData, top);
    insertVec3(m_vertexData, glm::normalize(glm::vec3(0, top[1], 0)));



}

void cylinder::wedger(float currentAngle, float nextAngle){
    //top cap
    float inc = 0.5/m_param1;

    //up cap
    for(int i = 0; i < m_param1; i++){
        glm::vec3 t_l = baseHelper(currentAngle, 0.5, (float) i * inc);
        glm::vec3 t_r = baseHelper(nextAngle, 0.5, (float) i * inc);
        glm::vec3 b_l = baseHelper(currentAngle, 0.5, (float) (i+1) * inc);
        glm::vec3 b_r = baseHelper(nextAngle, 0.5, (float) (i+1) * inc);
        makeBase(t_l, t_r, b_l, b_r);
    }

    for(int i = 0; i < m_param1; i++){
        glm::vec3 t_l = baseHelper(currentAngle, -0.5, (float) i * inc);
        glm::vec3 t_r = baseHelper(nextAngle, -0.5, (float) i * inc);
        glm::vec3 b_l = baseHelper(currentAngle, -0.5, (float) (i+1) * inc);
        glm::vec3 b_r = baseHelper(nextAngle, -0.5, (float) (i+1) * inc);
        makeBase(t_r, t_l, b_r, b_l);
    }

    //body data
    float y_inc = 1.0/m_param1;
    for (int i = 0; i < m_param1; i++){
        glm::vec3 t_l = wedgeHelper(currentAngle, y_inc * (float) i - 0.5);
        glm::vec3 t_r = wedgeHelper(nextAngle, y_inc * (float) i - 0.5);
        glm::vec3 b_l = wedgeHelper(currentAngle, y_inc * (float) (i+1) - 0.5);
        glm::vec3 b_r = wedgeHelper(nextAngle, y_inc * (float) (i+1) - 0.5);
        makeTile(t_l, t_r, b_l, b_r);

    }



}

void cylinder::makeCylinder(){
    float inc = 2.0 * M_PI / m_param2;

    for(int i = 0; i < m_param2; i++){
        wedger(inc * i, (i + 1) * inc);
    }
}


void cylinder::setVertexData() {
    // TODO for Project 5: Lights, Camera
    makeCylinder();
}

glm::vec3 cylinder::baseHelper(float angle, float y, float radialIncrement){
    return glm::vec3(radialIncrement * glm::sin(angle), y, radialIncrement * glm::cos(angle));
}

glm::vec3 cylinder::wedgeHelper(float angle, float y){
    return glm::vec3(0.5f * glm::sin(angle), y, 0.5f * glm::cos(angle));
}

// Inserts a glm::vec3 into a vector of floats.
// This will come in handy if you want to take advantage of vectors to build your shape!
void cylinder::insertVec3(std::vector<float> &data, glm::vec3 v) {
    data.push_back(v.x);
    data.push_back(v.y);
    data.push_back(v.z);
}
