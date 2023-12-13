//#include "cube.h"

//void cube::updateParams(int param1) {
//    m_vertexData = std::vector<float>();
//    m_param1 = param1;
//    setVertexData();
//}

//void cube::makeTile(glm::vec3 topLeft,
//                    glm::vec3 topRight,
//                    glm::vec3 bottomLeft,
//                    glm::vec3 bottomRight) {
//    // Task 2: create a tile (i.e. 2 triangles) based on 4 given points.
//    insertVec3(m_vertexData, topLeft);
//    insertVec3(m_vertexData, glm::normalize(glm::cross((bottomLeft - topLeft), (topRight - topLeft))));

//    insertVec3(m_vertexData, bottomLeft);
//    insertVec3(m_vertexData, -glm::normalize(glm::cross(-(bottomLeft - topLeft), (bottomRight - bottomLeft))));

//    insertVec3(m_vertexData, bottomRight);
//    insertVec3(m_vertexData, glm::normalize(glm::cross((topRight - bottomRight), (bottomLeft - bottomRight))));





//    insertVec3(m_vertexData, bottomRight);
//    insertVec3(m_vertexData, glm::normalize(glm::cross((topRight - bottomRight), (bottomLeft - bottomRight))));

//    insertVec3(m_vertexData, topRight);
//    insertVec3(m_vertexData, glm::normalize(glm::cross((topLeft - topRight), (bottomRight - topRight))));

//    insertVec3(m_vertexData, topLeft);
//    insertVec3(m_vertexData, glm::normalize(glm::cross((bottomLeft - topLeft), (topRight - topLeft))));
//}

//void cube::makeFace(glm::vec3 topLeft,
//                    glm::vec3 topRight,
//                    glm::vec3 bottomLeft,
//                    glm::vec3 bottomRight) {
//    // Task 3: create a single side of the cube out of the 4
//    //         given points and makeTile()
//    // Note: think about how param 1 affects the number of triangles on
//    //       the face of the cube
//    float scale = 1.0/m_param1;

//    glm::vec3 sideLenH = (topRight - topLeft) * scale;
//    glm::vec3 sideLenV = (bottomLeft - topLeft) * scale;
//    //    float x = topLeft[0];
//    //    float y = topLeft[1];

//    for(int j = 0; j < m_param1; j++){
//        for(int i = 0; i < m_param1; i++){
//            glm::vec3 topLeftN = topLeft + float(j) * sideLenH + float(i) * sideLenV;
//            glm::vec3 topRighttN = topLeftN + sideLenH ;
//            glm::vec3 bottomLeftN = topLeftN + sideLenV;
//            glm::vec3 bottomRightN = topLeftN + sideLenH + sideLenV;




//            makeTile(topLeftN, topRighttN, bottomLeftN, bottomRightN);




//        }
//    }




//}

//glm::vec3 decrementer(glm::vec3 p){
//    glm::vec3 dec(0.5f, 0.5f, 0.5f);
//    return p - dec;
//}


//void cube::setVertexData() {
//    // Uncomment these lines for Task 2, then comment them out for Task 3:

//    //     makeTile(glm::vec3(-0.5f,  0.5f, 0.5f),
//    //              glm::vec3( 0.5f,  0.5f, 0.5f),
//    //              glm::vec3(-0.5f, -0.5f, 0.5f),
//    //              glm::vec3( 0.5f, -0.5f, 0.5f));

//    // Uncomment these lines for Task 3:

//    //     makeFace(glm::vec3(-0.5f,  0.5f, 0.5f),
//    //                       glm::vec3( 0.5f,  0.5f, 0.5f),
//    //                       glm::vec3(-0.5f, -0.5f, 0.5f),
//    //                       glm::vec3( 0.5f, -0.5f, 0.5f));

//    //    makeFace(glm::vec3(-0.5f,  0.5f, 0.5f),
//    //             glm::vec3( 0.5f,  0.5f, 0.5f),
//    //             glm::vec3(-0.5f, -0.5f, 0.5f),
//    //             glm::vec3( 0.5f, -0.5f, 0.5f));



//    // Task 4: Use the makeFace() function to make all 6 sides of the cube
//    //front face
//    makeFace(glm::vec3(-0.5f,  0.5f, 0.5f),
//             glm::vec3( 0.5f,  0.5f, 0.5f),
//             glm::vec3(-0.5f, -0.5f, 0.5f),
//             glm::vec3( 0.5f, -0.5f, 0.5f));

//    //Task 4: Use the makeFace() function to make all 6 sides of the cube

//    //back face
//    makeFace(glm::vec3( 0.5f,  0.5f, -0.5f), //topLeft
//             glm::vec3(-0.5f,   0.5f, -0.5f), //topRight
//             glm::vec3( 0.5f,  -0.5f, -0.5f), //bottomLeft
//             glm::vec3(-0.5f,  -0.5f, -0.5f)); //bottomRight

//    //Left Face
//    makeFace(glm::vec3(0.5f,  0.5f,  0.5f), //topLeft
//             glm::vec3(0.5f,   0.5f,  -0.5f), //topRight
//             glm::vec3(0.5f,  -0.5f,  0.5f), //bottomLeft
//             glm::vec3(0.5f,  -0.5f, -0.5f)); //bottomRight

//    //Right Face
//    makeFace(glm::vec3(-0.5f,   0.5f,  -0.5f), //topRight
//             glm::vec3(-0.5f,  0.5f,  0.5f), //topLeft
//             glm::vec3(-0.5f,  -0.5f, -0.5f),
//             glm::vec3(-0.5f,  -0.5f,  0.5f)); //bottomLeft); //bottomRight


//    //top face
//    makeFace(glm::vec3(-0.5f,  -0.5f,  0.5f), //topLeft
//             glm::vec3( 0.5f, -0.5f,  0.5f), //topRight
//             glm::vec3(-0.5f, -0.5f, -0.5f), //bottomLeft
//             glm::vec3( 0.5f, -0.5f, -0.5f)); //bottomRight

//    //bottom face
//    makeFace(glm::vec3(-0.5f,  0.5f, -0.5f), //topLeft
//             glm::vec3( 0.5f,  0.5f, -0.5f), //topRight
//             glm::vec3(-0.5f, 0.5f,  0.5f), //bottomLeft
//             glm::vec3( 0.5f, 0.5f,  0.5f)); //bottomRight


//}

//// Inserts a glm::vec3 into a vector of floats.
//// This will come in handy if you want to take advantage of vectors to build your shape!
//void cube::insertVec3(std::vector<float> &data, glm::vec3 v) {
//    data.push_back(v.x);
//    data.push_back(v.y);
//    data.push_back(v.z);
//}

#include "cube.h"

void cube::updateParams(int param1) {
    m_vertexData = std::vector<float>();
    m_param1 = 3 * param1;
    setVertexData();
}

void cube::makeTile(glm::vec3 topLeft,
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

void cube::makeReverseTileOnly(glm::vec3 topLeft,
                               glm::vec3 topRight,
                               glm::vec3 bottomLeft,
                               glm::vec3 bottomRight) {
    // Task 2: create a tile (i.e. 2 triangles) based on 4 given points.


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

void cube::makeFace(glm::vec3 topLeft,
                    glm::vec3 topRight,
                    glm::vec3 bottomLeft,
                    glm::vec3 bottomRight, bool makeWindows) {
    // Task 3: create a single side of the cube out of the 4
    //         given points and makeTile()
    // Note: think about how param 1 affects the number of triangles on
    //       the face of the cube
    glm::vec3 x = 1.f / m_param1 * (topRight - topLeft);
    glm::vec3 y = 1.f / m_param1 * (bottomLeft - topLeft);
    for (int i = 0; i < m_param1; i++) {
        for (int j = 0; j < m_param1; j++) {
            float c = (float) i;
            float r = (float) j;
            glm::vec3 t_l = topLeft + r * x + c * y;
            glm::vec3 t_r = topLeft + (r + 1.f) * x + c * y;
            glm::vec3 b_l = topLeft + r * x + (c + 1.f) * y;
            glm::vec3 b_r = topLeft + (r + 1.f) * x + (c + 1.f) * y;


            if ((!(i % 3 == 1 && j % 3 == 1)) || (!makeWindows)) {
                makeTile(t_l, t_r, b_l, b_r);
            } else {
                makeReverseTileOnly(t_l, t_r, b_l, b_r);
            }
        }
    }


}

void cube::setVertexData() {
    // Uncomment these lines for Task 2, then comment them out for Task 3:

    //    makeTile(glm::vec3(-0.5f,  0.5f, 0.5f),
    //              glm::vec3( 0.5f,  0.5f, 0.5f),
    //              glm::vec3(-0.5f, -0.5f, 0.5f),
    //              glm::vec3( 0.5f, -0.5f, 0.5f));

    // Uncomment these lines for Task 3:

    makeFace(glm::vec3(-0.5f,  0.5f, 0.5f),
             glm::vec3( 0.5f,  0.5f, 0.5f),
             glm::vec3(-0.5f, -0.5f, 0.5f),
             glm::vec3(0.5f, -0.5f, 0.5f), true);

    // Task 4: Use the makeFace() function to make all 6 sides of the cube

    makeFace(glm::vec3(0.5f,  0.5f, -0.5f),
             glm::vec3(-0.5f, 0.5f, -0.5f),
             glm::vec3(0.5f, -0.5f, -0.5f),
             glm::vec3(-0.5f,-0.5f,-0.5f), true);

    makeFace(glm::vec3(-0.5f, -0.5f, 0.5f),
             glm::vec3(0.5f,  -0.5f, 0.5f),
             glm::vec3(-0.5f,-0.5f, -0.5f),
             glm::vec3(0.5f,-0.5f,-0.5f), false);

    makeFace(glm::vec3( 0.5f,  0.5f, 0.5f),
             glm::vec3(-0.5f,  0.5f, 0.5f),
             glm::vec3(0.5f,  0.5f, -0.5f),
             glm::vec3(-0.5f, 0.5f,-0.5f), false);

    makeFace(glm::vec3(-0.5f, 0.5f, -0.5f),
             glm::vec3(-0.5f,  0.5f, 0.5f),
             glm::vec3(-0.5f, -0.5f,-0.5f),
             glm::vec3(-0.5f, -0.5f,0.5f), true);

    makeFace(glm::vec3(0.5f,  0.5f,  0.5f),
             glm::vec3(0.5f,  0.5f, -0.5f),
             glm::vec3(0.5f, -0.5f,  0.5f),
             glm::vec3(0.5f, -0.5f,-0.5f), true);
}

// Inserts a glm::vec3 into a vector of floats.
// This will come in handy if you want to take advantage of vectors to build your shape!
void cube::insertVec3(std::vector<float> &data, glm::vec3 v) {
    data.push_back(v.x);
    data.push_back(v.y);
    data.push_back(v.z);
}


