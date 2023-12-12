#include "cone.h"

void cone::updateParams(int param1, int param2) {
    m_vertexData = std::vector<float>();
    m_param1 = param1;
    m_param2 = param2;
    setVertexData();
}

void cone::makeTile(glm::vec3 topLeft,
                    glm::vec3 topRight,
                    glm::vec3 bottomLeft,
                    glm::vec3 bottomRight){

    if(bottomLeft[1] > 0.499){

        float normalTipX = (topLeft[0] + topRight[0]) / 2.0;
        float normalTipZ = (topLeft[2] + topRight[2]) / 2.0;
        glm::vec3 normalTip(normalTipX, 1.0/m_param1, normalTipZ);

        insertVec3(m_vertexData, bottomRight);
        insertVec3(m_vertexData, glm::normalize(normalTip));

        insertVec3(m_vertexData, bottomLeft);
        insertVec3(m_vertexData, glm::normalize(normalTip));

        insertVec3(m_vertexData, topLeft);
        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * topLeft[0], 0.25 - (0.5 * topLeft[1]), 2.0 * topLeft[2])));

        insertVec3(m_vertexData, topLeft);
        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * topLeft[0], 0.25 - (0.5 * topLeft[1]), 2.0 * topLeft[2])));

        insertVec3(m_vertexData, topRight);
        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * topRight[0], 0.25 - (0.5 * topRight[1]), 2.0 * topRight[2])));

        insertVec3(m_vertexData, bottomRight);
        insertVec3(m_vertexData, glm::normalize(normalTip));

    }
    else{
        insertVec3(m_vertexData, bottomRight);
        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * bottomRight[0], 0.25 - (0.5 * bottomRight[1]), 2.0 * bottomRight[2])));

        insertVec3(m_vertexData, bottomLeft);
        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * bottomLeft[0], 0.25 - (0.5 * bottomLeft[1]), 2.0 * bottomLeft[2])));

        insertVec3(m_vertexData, topLeft);
        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * topLeft[0], 0.25 - (0.5 * topLeft[1]), 2.0 * topLeft[2])));

        insertVec3(m_vertexData, topLeft);
        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * topLeft[0], 0.25 - (0.5 * topLeft[1]), 2.0 * topLeft[2])));

        insertVec3(m_vertexData, topRight);
        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * topRight[0], 0.25 - (0.5 * topRight[1]), 2.0 * topRight[2])));

        insertVec3(m_vertexData, bottomRight);
        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * bottomRight[0], 0.25 - (0.5 * bottomRight[1]), 2.0 * bottomRight[2])));

    }

}

void cone::makeCapTile(glm::vec3 topLeft,
                       glm::vec3 topRight,
                       glm::vec3 bottomLeft,
                       glm::vec3 bottomRight){

    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, glm::normalize(glm::vec3(0, topLeft[1], 0)));
    insertVec3(m_vertexData, bottomLeft);
    insertVec3(m_vertexData, glm::normalize(glm::vec3(0, bottomLeft[1], 0)));
    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, glm::normalize(glm::vec3(0, bottomRight[1], 0)));

    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, glm::normalize(glm::vec3(0, bottomRight[1], 0)));
    insertVec3(m_vertexData, topRight);
    insertVec3(m_vertexData, glm::normalize(glm::vec3(0, topRight[1], 0)));
    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, glm::normalize(glm::vec3(0, topLeft[1], 0)));




}

glm::vec3 cone::baseHelper(float theta, float y, float inc){
    return glm::vec3(inc * glm::sin(theta), y, inc * glm::cos(theta));
}

glm::vec3 cone::wedgeHelper(float angle, float y, int index){
    float weight = (float) (m_param1 - index)/ (float) m_param1;
    return glm::vec3(weight * 0.5f * glm::sin(angle), y, weight * 0.5f * glm::cos(angle));

}

void cone::wedger(float currAngle,float nextAngle){
    float inc = 0.5/m_param1;

    for(int i = 0; i < m_param1; i++){
        glm::vec3 t1 = baseHelper(currAngle, -0.5, (float) i * inc);
        glm::vec3 t2 = baseHelper(nextAngle, -0.5, (float) i * inc);
        glm::vec3 b1 = baseHelper(currAngle, -0.5, (float) (i+1) * inc);
        glm::vec3 b2 = baseHelper(nextAngle, -0.5, (float) (i+1) * inc);
        makeCapTile(t2, t1, b2, b1);
    }


    float vertInc = 1.0/ m_param1;
    for(int i = 0; i < m_param1; i++){
        glm::vec3 t1 = wedgeHelper(currAngle, vertInc * (float) i - 0.5, i);
        glm::vec3 t2 = wedgeHelper(nextAngle, vertInc * (float) i - 0.5, i);
        glm::vec3 b1 = wedgeHelper(currAngle, vertInc * (float) (i+1) - 0.5, i+1);
        glm::vec3 b2 = wedgeHelper(nextAngle, vertInc * (float) (i+1) - 0.5, i+1);
        makeTile(t1, t2, b1, b2);
    }

}


void cone::makeCone(){
    float increment = 2.0 * (M_PI/ m_param2);
    for(int j = 0; j < m_param2; j++){
        wedger(increment * j, (j + 1) * increment);
    }
}


void cone::setVertexData() {
    makeCone();
}


// Inserts a glm::vec3 into a vector of floats.
// This will come in handy if you want to take advantage of vectors to build your shape!
void cone::insertVec3(std::vector<float> &data, glm::vec3 v) {
    data.push_back(v.x);
    data.push_back(v.y);
    data.push_back(v.z);
}


