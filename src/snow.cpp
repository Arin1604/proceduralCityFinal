#include "snow.h"

//IS RECENT

void snow::insertVecData(std::vector<float> &data, std::vector<float> v){
    for(int i = 0; i < v.size(); i++){
        data.push_back(v[i]);
    }

}

void snow::snowMaker(float size, int maxParticles, int width, int height){
//    for(int i = 0; i <= maxParticles; i++){
//        int xRandomizer = 1;//i * rand() % width;
//        int yRandomizer = 1;//i * rand() % height;

//        std::vector<float> snowData =
//            { //     POSITIONS    //
////            -size + xRandomizer,  size + yRandomizer, 0.f, 0.f, 1.f,
////            -size + xRandomizer, -size + yRandomizer, 0.f, 0.f, 0.f,
////            size + xRandomizer, -size + yRandomizer, 0.f, 1.f, 0.f,
////            size + xRandomizer,  size + yRandomizer, 0.f, 1.f, 1.f,
////            -size + xRandomizer,  size + yRandomizer, 0.f, 0.f, 1.f,
////            size + xRandomizer, -size + yRandomizer, 0.f, 1.f, 0.f
//                                       -0.5f + i,  0.5f+ i, 0.f+ i, 0.f, 0.5f,
//                                       -0.5f+ i, -0.5f+ i, 0.f+ i, 0.f, 0.f,
//                                       0.5f+ i, -0.5f+ i, 0.f+ i, 0.5f, 0.f,
//                                       0.5f+ i,  0.5f+ i, 0.f+ i, 0.5f, 0.5f,
//                                       -0.5f+ i,  0.5f+ i, 0.f+ i, 0.f, 0.5f,
//                                       0.5f+ i, -0.5f+ i, 0.f+ i, 0.5f, 0.f
//            };

//        insertVecData(m_vertexData, snowData);




//    }
    std::vector<float> snowData =
                    { //     POSITIONS    //
        //            -size + xRandomizer,  size + yRandomizer, 0.f, 0.f, 1.f,
        //            -size + xRandomizer, -size + yRandomizer, 0.f, 0.f, 0.f,
        //            size + xRandomizer, -size + yRandomizer, 0.f, 1.f, 0.f,
        //            size + xRandomizer,  size + yRandomizer, 0.f, 1.f, 1.f,
        //            -size + xRandomizer,  size + yRandomizer, 0.f, 0.f, 1.f,
        //            size + xRandomizer, -size + yRandomizer, 0.f, 1.f, 0.f
        -size,  size, 0.f, 0.f, size,
        -size, -size, 0.f, 0.f, 0.f,
        size, -size, 0.f, size, 0.f,
        size,  size, 0.f, size, size,
        -size,  size, 0.f, 0.f, size,
        size, -size, 0.f, size, 0.f,};

    insertVecData(m_vertexData, snowData);

}
