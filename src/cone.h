#pragma once

#include <vector>
#include <glm/glm.hpp>

class cone
{
public:
    void updateParams(int param1);
    std::vector<float> generateShape(bool roof);

private:
    void insertVec3(std::vector<float> &data, glm::vec3 v);
    void setVertexData();
    void makeTile(glm::vec3 topLeft,
                  glm::vec3 topRight,
                  glm::vec3 bottomLeft,
                  glm::vec3 bottomRight);
    void makeFace(glm::vec3 topLeft,
                  glm::vec3 topRight,
                  glm::vec3 bottomLeft,
                  glm::vec3 bottomRight);
    void makeWindow(glm::vec3 topLeft,
                    glm::vec3 topRight,
                    glm::vec3 bottomLeft,
                    glm::vec3 bottomRight);

    void makeWedge(float currTheta, float nextTheta);
    void makeCone();
    void makeRoofTile(glm::vec3 topLeft,
                      glm::vec3 topRight,
                      glm::vec3 bottomLeft,
                      glm::vec3 bottomRight);
    glm::vec3 wedgeHelper(float theta, float height, int i);

    std::vector<float> m_vertexData;
    int m_param1;

};

