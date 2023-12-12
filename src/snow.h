#pragma once

#include <vector>
#include <glm/glm.hpp>

//IS RECENT
class snow
{
public:
    void snowMaker(float size, int maxParticles, int width, int height);
    std::vector<float> generateShape() { return m_vertexData; }

private:
    void insertVecData(std::vector<float> &data, std::vector<float> v);
//    void setVertexData();
//    void makeTile(glm::vec3 topLeft,
//                  glm::vec3 topRight,
//                  glm::vec3 bottomLeft,
//                  glm::vec3 bottomRight);
//    void makeWedge(float currTheta, float nextTheta);
//    void makeSphere();

    std::vector<float> m_vertexData;
//    float m_radius = 0.5;
//    int m_param1;
//    int m_param2;
};
