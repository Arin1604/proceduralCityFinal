#include "cylinder.h"

void cylinder::updateParams(int param1, int param2) {
    m_vertexData = std::vector<float>();

    int param_2 = 16;

    if (param2 < 2) {
        param_2 = 4;
    }
    m_param1 = 18;
    m_param2 = param_2;
    setVertexData();
}

void cylinder::makeTile(glm::vec3 topLeft,
                        glm::vec3 topRight,
                        glm::vec3 bottomLeft,
                        glm::vec3 bottomRight) {
    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * bottomRight[0], 0.0, 2.0 * bottomRight[2])));
    insertVec3(m_vertexData, bottomLeft);
    insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * bottomLeft[0], 0.0, 2.0 * bottomLeft[2])));
    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * topLeft[0], 0.0, 2.0 * topLeft[2])));


    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * topLeft[0], 0.0, 2.0 * topLeft[2])));

    insertVec3(m_vertexData, topRight);
    insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * topRight[0], 0.0, 2.0 * topRight[2])));

    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * bottomRight[0], 0.0, 2.0 * bottomRight[2])));

    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, -glm::normalize(glm::vec3(2.0 * bottomRight[0], 0.0, 2.0 * bottomRight[2])));

    insertVec3(m_vertexData, topRight);
    insertVec3(m_vertexData, -glm::normalize(glm::vec3(2.0 * topRight[0], 0.0, 2.0 * topRight[2])));

    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, -glm::normalize(glm::vec3(2.0 * topLeft[0], 0.0, 2.0 * topLeft[2])));

    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, -glm::normalize(glm::vec3(2.0 * topLeft[0], 0.0, 2.0 * topLeft[2])));

    insertVec3(m_vertexData, bottomLeft);
    insertVec3(m_vertexData, -glm::normalize(glm::vec3(2.0 * bottomLeft[0], 0.0, 2.0 * bottomLeft[2])));

    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, -glm::normalize(glm::vec3(2.0 * bottomRight[0], 0.0, 2.0 * bottomRight[2])));
}

void cylinder::makeReverseTileOnly(glm::vec3 topLeft,
                                   glm::vec3 topRight,
                                   glm::vec3 bottomLeft,
                                   glm::vec3 bottomRight) {
    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, -glm::normalize(glm::vec3(2.0 * bottomRight[0], 0.0, 2.0 * bottomRight[2])));

    insertVec3(m_vertexData, topRight);
    insertVec3(m_vertexData, -glm::normalize(glm::vec3(2.0 * topRight[0], 0.0, 2.0 * topRight[2])));

    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, -glm::normalize(glm::vec3(2.0 * topLeft[0], 0.0, 2.0 * topLeft[2])));

    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, -glm::normalize(glm::vec3(2.0 * topLeft[0], 0.0, 2.0 * topLeft[2])));

    insertVec3(m_vertexData, bottomLeft);
    insertVec3(m_vertexData, -glm::normalize(glm::vec3(2.0 * bottomLeft[0], 0.0, 2.0 * bottomLeft[2])));

    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, -glm::normalize(glm::vec3(2.0 * bottomRight[0], 0.0, 2.0 * bottomRight[2])));

}

void cylinder::makeCapTile(glm::vec3 topLeft,
                           glm::vec3 topRight,
                           glm::vec3 bottomLeft,
                           glm::vec3 bottomRight) {
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

    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, -glm::normalize(glm::vec3(0, topLeft[1], 0)));

    insertVec3(m_vertexData, topRight);
    insertVec3(m_vertexData, -glm::normalize(glm::vec3(0, topRight[1], 0)));

    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, -glm::normalize(glm::vec3(0, bottomRight[1], 0)));

    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, -glm::normalize(glm::vec3(0, bottomRight[1], 0)));

    insertVec3(m_vertexData, bottomLeft);
    insertVec3(m_vertexData, -glm::normalize(glm::vec3(0, bottomLeft[1], 0)));

    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, -glm::normalize(glm::vec3(0, topLeft[1], 0)));

}

void cylinder::makeWedge(float currentTheta, float nextTheta, int incr) {
    //top cap
    float radial_inc = 0.5 / m_param1;
    for (int i = 0; i < m_param1; i++) {
        glm::vec3 t_l = capHelper(currentTheta, 0.5, (float) i * radial_inc);
        glm::vec3 t_r = capHelper(nextTheta, 0.5, (float) i * radial_inc);
        glm::vec3 b_l = capHelper(currentTheta, 0.5, (float) (i + 1) * radial_inc);
        glm::vec3 b_r = capHelper(nextTheta, 0.5, (float) (i + 1) * radial_inc);
        makeCapTile(t_l, t_r, b_l, b_r);
    }

    for (int i = 0; i < m_param1; i++) {
        glm::vec3 t_r = capHelper(currentTheta, -0.5, (float) i * radial_inc);
        glm::vec3 t_l = capHelper(nextTheta, -0.5, (float) i * radial_inc);
        glm::vec3 b_r = capHelper(currentTheta, -0.5, (float) (i + 1) * radial_inc);
        glm::vec3 b_l = capHelper(nextTheta, -0.5, (float) (i + 1) * radial_inc);
        makeCapTile(t_l, t_r, b_l, b_r);
    }


    //body
    float y_inc = 1.0 / m_param1;
    for (int i = 0; i < m_param1; i++) {
        glm::vec3 t_l = wedgeHelper(currentTheta, y_inc * (float) i - 0.5);
        glm::vec3 t_r = wedgeHelper(nextTheta, y_inc * (float) i - 0.5);
        glm::vec3 b_l = wedgeHelper(currentTheta, y_inc * (float) (i + 1) - 0.5);
        glm::vec3 b_r = wedgeHelper(nextTheta, y_inc * (float) (i + 1) - 0.5);
        if (!(i % 3 == 1 && incr % 2 == 0)) {
            makeTile(t_l, t_r, b_l, b_r);
        } else {
            makeReverseTileOnly(t_l, t_r, b_l, b_r);
        }
    }

}

glm::vec3 cylinder::capHelper(float theta, float y, float radial_inc) {
    return glm::vec3(radial_inc * glm::sin(theta), y, radial_inc * glm::cos(theta));
}

void cylinder::makeCylinder() {
    float inc = 2.0 * M_PI / m_param2;
    float two_pi = 2.0 * M_PI;
    for (int i = 0; i < m_param2; i++) {
        makeWedge(inc * i, (i + 1) * inc, i);
    }
}

void cylinder::setVertexData() {
    makeCylinder();
}


void cylinder::insertVec3(std::vector<float> &data, glm::vec3 v) {
    data.push_back(v.x);
    data.push_back(v.y);
    data.push_back(v.z);
}

glm::vec3 cylinder::wedgeHelper(float theta, float y) {
    return glm::vec3(0.5f * glm::sin(theta), y, 0.5f * glm::cos(theta));
}

