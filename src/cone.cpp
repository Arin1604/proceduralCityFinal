//#include "cone.h"

//void cone::updateParams(int param1, int param2) {
//    m_vertexData = std::vector<float>();
//    m_param1 = param1;
//    m_param2 = param2;
//    setVertexData();
//}

//void cone::makeTile(glm::vec3 topLeft,
//                    glm::vec3 topRight,
//                    glm::vec3 bottomLeft,
//                    glm::vec3 bottomRight){

//    if(bottomLeft[1] > 0.499){

//        float normalTipX = (topLeft[0] + topRight[0]) / 2.0;
//        float normalTipZ = (topLeft[2] + topRight[2]) / 2.0;
//        glm::vec3 normalTip(normalTipX, 1.0/m_param1, normalTipZ);

//        insertVec3(m_vertexData, bottomRight);
//        insertVec3(m_vertexData, glm::normalize(normalTip));

//        insertVec3(m_vertexData, bottomLeft);
//        insertVec3(m_vertexData, glm::normalize(normalTip));

//        insertVec3(m_vertexData, topLeft);
//        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * topLeft[0], 0.25 - (0.5 * topLeft[1]), 2.0 * topLeft[2])));

//        insertVec3(m_vertexData, topLeft);
//        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * topLeft[0], 0.25 - (0.5 * topLeft[1]), 2.0 * topLeft[2])));

//        insertVec3(m_vertexData, topRight);
//        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * topRight[0], 0.25 - (0.5 * topRight[1]), 2.0 * topRight[2])));

//        insertVec3(m_vertexData, bottomRight);
//        insertVec3(m_vertexData, glm::normalize(normalTip));

//    }
//    else{
//        insertVec3(m_vertexData, bottomRight);
//        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * bottomRight[0], 0.25 - (0.5 * bottomRight[1]), 2.0 * bottomRight[2])));

//        insertVec3(m_vertexData, bottomLeft);
//        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * bottomLeft[0], 0.25 - (0.5 * bottomLeft[1]), 2.0 * bottomLeft[2])));

//        insertVec3(m_vertexData, topLeft);
//        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * topLeft[0], 0.25 - (0.5 * topLeft[1]), 2.0 * topLeft[2])));

//        insertVec3(m_vertexData, topLeft);
//        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * topLeft[0], 0.25 - (0.5 * topLeft[1]), 2.0 * topLeft[2])));

//        insertVec3(m_vertexData, topRight);
//        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * topRight[0], 0.25 - (0.5 * topRight[1]), 2.0 * topRight[2])));

//        insertVec3(m_vertexData, bottomRight);
//        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * bottomRight[0], 0.25 - (0.5 * bottomRight[1]), 2.0 * bottomRight[2])));

//    }

//}

//void cone::makeCapTile(glm::vec3 topLeft,
//                       glm::vec3 topRight,
//                       glm::vec3 bottomLeft,
//                       glm::vec3 bottomRight){

//    insertVec3(m_vertexData, topLeft);
//    insertVec3(m_vertexData, glm::normalize(glm::vec3(0, topLeft[1], 0)));
//    insertVec3(m_vertexData, bottomLeft);
//    insertVec3(m_vertexData, glm::normalize(glm::vec3(0, bottomLeft[1], 0)));
//    insertVec3(m_vertexData, bottomRight);
//    insertVec3(m_vertexData, glm::normalize(glm::vec3(0, bottomRight[1], 0)));

//    insertVec3(m_vertexData, bottomRight);
//    insertVec3(m_vertexData, glm::normalize(glm::vec3(0, bottomRight[1], 0)));
//    insertVec3(m_vertexData, topRight);
//    insertVec3(m_vertexData, glm::normalize(glm::vec3(0, topRight[1], 0)));
//    insertVec3(m_vertexData, topLeft);
//    insertVec3(m_vertexData, glm::normalize(glm::vec3(0, topLeft[1], 0)));




//}

//glm::vec3 cone::baseHelper(float theta, float y, float inc){
//    return glm::vec3(inc * glm::sin(theta), y, inc * glm::cos(theta));
//}

//glm::vec3 cone::wedgeHelper(float angle, float y, int index){
//    float weight = (float) (m_param1 - index)/ (float) m_param1;
//    return glm::vec3(weight * 0.5f * glm::sin(angle), y, weight * 0.5f * glm::cos(angle));

//}

//void cone::wedger(float currAngle,float nextAngle){
//    float inc = 0.5/m_param1;

//    for(int i = 0; i < m_param1; i++){
//        glm::vec3 t1 = baseHelper(currAngle, -0.5, (float) i * inc);
//        glm::vec3 t2 = baseHelper(nextAngle, -0.5, (float) i * inc);
//        glm::vec3 b1 = baseHelper(currAngle, -0.5, (float) (i+1) * inc);
//        glm::vec3 b2 = baseHelper(nextAngle, -0.5, (float) (i+1) * inc);
//        makeCapTile(t2, t1, b2, b1);
//    }


//    float vertInc = 1.0/ m_param1;
//    for(int i = 0; i < m_param1; i++){
//        glm::vec3 t1 = wedgeHelper(currAngle, vertInc * (float) i - 0.5, i);
//        glm::vec3 t2 = wedgeHelper(nextAngle, vertInc * (float) i - 0.5, i);
//        glm::vec3 b1 = wedgeHelper(currAngle, vertInc * (float) (i+1) - 0.5, i+1);
//        glm::vec3 b2 = wedgeHelper(nextAngle, vertInc * (float) (i+1) - 0.5, i+1);
//        makeTile(t1, t2, b1, b2);
//    }

//}


//void cone::makeCone(){
//    float increment = 2.0 * (M_PI/ m_param2);
//    for(int j = 0; j < m_param2; j++){
//        wedger(increment * j, (j + 1) * increment);
//    }
//}


//void cone::setVertexData() {
//    makeCone();
//}


//// Inserts a glm::vec3 into a vector of floats.
//// This will come in handy if you want to take advantage of vectors to build your shape!
//void cone::insertVec3(std::vector<float> &data, glm::vec3 v) {
//    data.push_back(v.x);
//    data.push_back(v.y);
//    data.push_back(v.z);
//}

#include "cone.h"



void cone::updateParams(int param1) {
    m_vertexData = std::vector<float>();
    m_param1 = 3 * 5;
    setVertexData();
}

std::vector<float> cone::generateShape(bool roof) {
    if (roof) {
        makeCone();
    }
    return m_vertexData;
}

void cone::makeTile(glm::vec3 topLeft,
                     glm::vec3 topRight,
                     glm::vec3 bottomLeft,
                     glm::vec3 bottomRight) {
    // Task 2: create a tile (i.e. 2 triangles) based on 4 given points.
    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, glm::normalize(glm::cross(bottomLeft - topLeft, topRight - topLeft)));

    insertVec3(m_vertexData, bottomLeft);
    insertVec3(m_vertexData, glm::normalize(glm::cross(bottomRight - bottomLeft, topLeft - bottomLeft)));
    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, glm::normalize(glm::cross(topRight - bottomRight, bottomLeft - bottomRight)));
    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, glm::normalize(glm::cross(topRight - bottomRight, bottomLeft - bottomRight)));
    insertVec3(m_vertexData, topRight);
    insertVec3(m_vertexData, glm::normalize(glm::cross(bottomRight - bottomLeft, topLeft - bottomLeft)));
    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, glm::normalize(glm::cross(bottomLeft - topLeft, topRight - topLeft)));

    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, -glm::normalize(glm::cross(topRight - bottomRight, bottomLeft - bottomRight)));

    insertVec3(m_vertexData, bottomLeft);
    insertVec3(m_vertexData, -glm::normalize(glm::cross(bottomRight - bottomLeft, topLeft - bottomLeft)));

    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, -glm::normalize(glm::cross(bottomLeft - topLeft, topRight - topLeft)));

    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, -glm::normalize(glm::cross(bottomLeft - topLeft, topRight - topLeft)));

    insertVec3(m_vertexData, topRight);
    insertVec3(m_vertexData, -glm::normalize(glm::cross(bottomRight - bottomLeft, topLeft - bottomLeft)));

    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, -glm::normalize(glm::cross(topRight - bottomRight, bottomLeft - bottomRight)));


}

void cone::makeWindow(glm::vec3 topLeft,
                       glm::vec3 topRight,
                       glm::vec3 bottomLeft,
                       glm::vec3 bottomRight) {

}

void cone::makeFace(glm::vec3 topLeft,
                     glm::vec3 topRight,
                     glm::vec3 bottomLeft,
                     glm::vec3 bottomRight) {
    // Task 3: create a single side of the House out of the 4
    //         given points and makeTile()
    // Note: think about how param 1 affects the number of triangles on
    //       the face of the House
    glm::vec3 x = 1.f / m_param1 * (topRight - topLeft);
    glm::vec3 y = 1.f / m_param1 * (bottomLeft - topLeft);
    for (int i = 0; i < m_param1; i++) {
        for (int j = 0; j < m_param1; j++) {
            float c = (float) i;
            float r = (float) j;
            if (!(i % 3 == 1 && j % 3 == 1)) {
                glm::vec3 t_l = topLeft + r * x + c * y;
                glm::vec3 t_r = topLeft + (r + 1.f) * x + c * y;
                glm::vec3 b_l = topLeft + r * x + (c + 1.f) * y;
                glm::vec3 b_r = topLeft + (r + 1.f) * x + (c + 1.f) * y;
                makeTile(t_l, t_r, b_l, b_r);
            }
        }
    }


}

void cone::setVertexData() {
    // Uncomment these lines for Task 2, then comment them out for Task 3:

    //    makeTile(glm::vec3(-0.5f,  0.5f, 0.5f),
    //              glm::vec3( 0.5f,  0.5f, 0.5f),
    //              glm::vec3(-0.5f, -0.5f, 0.5f),
    //              glm::vec3( 0.5f, -0.5f, 0.5f));

    // Uncomment these lines for Task 3:

    makeFace(glm::vec3(-0.5f,  0.5f, 0.5f),
             glm::vec3( 0.5f,  0.5f, 0.5f),
             glm::vec3(-0.5f, -0.5f, 0.5f),
             glm::vec3(0.5f, -0.5f, 0.5f));

    // Task 4: Use the makeFace() function to make all 6 sides of the House

    makeFace(glm::vec3(0.5f,  0.5f, -0.5f),
             glm::vec3(-0.5f, 0.5f, -0.5f),
             glm::vec3(0.5f, -0.5f, -0.5f),
             glm::vec3(-0.5f,-0.5f,-0.5f));

    makeFace(glm::vec3(-0.5f, -0.5f, 0.5f),
             glm::vec3(0.5f,  -0.5f, 0.5f),
             glm::vec3(-0.5f,-0.5f, -0.5f),
             glm::vec3(0.5f,-0.5f,-0.5f));

    makeFace(glm::vec3( 0.5f,  0.5f, 0.5f),
             glm::vec3(-0.5f,  0.5f, 0.5f),
             glm::vec3(0.5f,  0.5f, -0.5f),
             glm::vec3(-0.5f, 0.5f,-0.5f));

    makeFace(glm::vec3(-0.5f, 0.5f, -0.5f),
             glm::vec3(-0.5f,  0.5f, 0.5f),
             glm::vec3(-0.5f, -0.5f,-0.5f),
             glm::vec3(-0.5f, -0.5f,0.5f));

    makeFace(glm::vec3(0.5f,  0.5f,  0.5f),
             glm::vec3(0.5f,  0.5f, -0.5f),
             glm::vec3(0.5f, -0.5f,  0.5f),
             glm::vec3(0.5f, -0.5f,-0.5f));
}

// Inserts a glm::vec3 into a vector of floats.
// This will come in handy if you want to take advantage of vectors to build your shape!
void cone::insertVec3(std::vector<float> &data, glm::vec3 v) {
    data.push_back(v.x);
    data.push_back(v.y);
    data.push_back(v.z);
}

void cone::makeRoofTile(glm::vec3 topLeft,
                         glm::vec3 topRight,
                         glm::vec3 bottomLeft,
                         glm::vec3 bottomRight) {

    if (bottomLeft[1] > 0.999) {

        float tip_norm_x = (topLeft[0] + topRight[0]) / 2.0;
        float tip_norm_z = (topLeft[2] + topRight[2]) / 2.0;
        glm::vec3 tip_normal(tip_norm_x, 1.0 / 4.f, tip_norm_z);

        insertVec3(m_vertexData, bottomRight);
        insertVec3(m_vertexData, glm::normalize(tip_normal));

        insertVec3(m_vertexData, bottomLeft);
        insertVec3(m_vertexData, glm::normalize(tip_normal));

        insertVec3(m_vertexData, topLeft);
        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * topLeft[0], 1.0f - (topLeft[1] - 0.75f), 2.0 * topLeft[2])));

        insertVec3(m_vertexData, topLeft);
        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * topLeft[0], 1.0f - (topLeft[1] - 0.75f), 2.0 * topLeft[2])));

        insertVec3(m_vertexData, topRight);
        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * topRight[0], 1.0f - (topRight[1] - 0.75f), 2.0 * topRight[2])));

        insertVec3(m_vertexData, bottomRight);
        insertVec3(m_vertexData, glm::normalize(tip_normal));
    } else {
        insertVec3(m_vertexData, bottomRight);
        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * bottomRight[0],  1.0f - (bottomRight[1] - 0.75f), 2.0 * bottomRight[2])));

        insertVec3(m_vertexData, bottomLeft);
        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * bottomLeft[0], 1.0f - (bottomLeft[1] - 0.75f), 2.0 * bottomLeft[2])));

        insertVec3(m_vertexData, topLeft);
        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * topLeft[0], 1.0f - (topLeft[1] - 0.75f), 2.0 * topLeft[2])));

        insertVec3(m_vertexData, topLeft);
        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * topLeft[0], 1.0f - (topLeft[1] - 0.75f), 2.0 * topLeft[2])));

        insertVec3(m_vertexData, topRight);
        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * topRight[0], 1.0f - (topRight[1] - 0.75f), 2.0 * topRight[2])));

        insertVec3(m_vertexData, bottomRight);
        insertVec3(m_vertexData, glm::normalize(glm::vec3(2.0 * bottomRight[0], 1.0f - (bottomRight[1] - 0.75f), 2.0 * bottomRight[2])));


    }

}

void cone::makeCone() {
    float inc = 2.0 * M_PI / 4.f;
    float pi_by_four = M_PI / 4.f;
    for (int i = 0; i < 4; i++) {
        makeWedge(inc * i + pi_by_four, (i + 1) * inc + pi_by_four);
    }
}

glm::vec3 cone::wedgeHelper(float theta, float y, int index) {
    float scale = (float) (m_param1 - index) / (float) m_param1;
    return glm::vec3(scale * sqrt(2.f) / 2.f * glm::sin(theta), y / 2.f + 0.75f, scale * sqrt(2.f) / 2.f * glm::cos(theta));
}

void cone::makeWedge(float currentTheta, float nextTheta) {
    //body
    float y_inc = 1.0 / m_param1;
    for (int i = 0; i < m_param1; i++) {
        glm::vec3 t_l = wedgeHelper(currentTheta, y_inc * (float) i - 0.5, i);
        glm::vec3 t_r = wedgeHelper(nextTheta, y_inc * (float) i - 0.5, i);
        glm::vec3 b_l = wedgeHelper(currentTheta, y_inc * (float) (i + 1) - 0.5, i + 1);
        glm::vec3 b_r = wedgeHelper(nextTheta, y_inc * (float) (i + 1) - 0.5, i + 1);
        makeRoofTile(t_l, t_r, b_l, b_r);
    }

}



