//IS SNOWFINAL

#include "realtime.h"

#include <QCoreApplication>
#include <QMouseEvent>
#include <QKeyEvent>
#include <iostream>
#include "cube.h"
#include "settings.h"
#include "sphere.h"
#include "utils/shaderloader.h"
#define GLM_ENABLE_EXPERIMENTAL

#include <random>
#include "Building.h"

//#include "glrenderer.h"

//#include <QCoreApplication>
//#include "src/shaderloader.h"

//#include <QMouseEvent>
#include "glm/gtc/constants.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

// ================== Project 5: Lights, Camera



Realtime::Realtime(QWidget *parent):
    camera(metaData.cameraData, size().width(), size().height(), settings.nearPlane, settings.farPlane)
    ,QOpenGLWidget(parent)
{
    m_prev_mouse_pos = glm::vec2(size().width()/2, size().height()/2);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);

    m_keyMap[Qt::Key_W]       = false;
    m_keyMap[Qt::Key_A]       = false;
    m_keyMap[Qt::Key_S]       = false;
    m_keyMap[Qt::Key_D]       = false;
    m_keyMap[Qt::Key_Control] = false;
    m_keyMap[Qt::Key_Space]   = false;

    // If you must use this function, do not edit anything above this
}

glm::vec4 sphericalToCartesian(float phi, float theta)
{
    return glm::vec4(glm::cos(theta) * glm::sin(phi),
                     glm::sin(theta) * glm::sin(phi),
                     glm::cos(phi),1);
}

void pushVec3(glm::vec4 vec, std::vector<float>* data)
{
    data->push_back(vec.x);
    data->push_back(vec.y);
    data->push_back(vec.z);
}

std::vector<float> generateSphereData(int phiTesselations, int thetaTesselations)
{
    std::vector<float> data;

    data.clear();
    data.reserve(phiTesselations * thetaTesselations * 6 * 3);

    for(int iTheta = 0; iTheta < thetaTesselations; iTheta++) {
        for(int iPhi = 0; iPhi < phiTesselations; iPhi++) {
            float phi1 = 1.0  * iPhi / phiTesselations * glm::pi<float>();
            float phi2 = 1.0  * (iPhi + 1) / phiTesselations * glm::pi<float>();

            float the1 = 1.0 * iTheta / thetaTesselations * 2 * glm::pi<float>();
            float the2 = 1.0 * (iTheta + 1) / thetaTesselations * 2 * glm::pi<float>();

            glm::vec4 p1 = sphericalToCartesian(phi1,the1);
            glm::vec4 p2 = sphericalToCartesian(phi2,the1);
            glm::vec4 p3 = sphericalToCartesian(phi2,the2);
            glm::vec4 p4 = sphericalToCartesian(phi1,the2);

            pushVec3(p1,&data);
            pushVec3(p2,&data);
            pushVec3(p3,&data);

            pushVec3(p1,&data);
            pushVec3(p3,&data);
            pushVec3(p4,&data);
        }
    }

    return data;
}


float Realtime::getRandomFloat(float min, float max) {
    // Use the Mersenne Twister random number generator
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 eng(rd()); // Seed the generator
    std::uniform_real_distribution<> distr(min, max); // Define the range

    return distr(eng);
}

// for final project generating city
void Realtime::GenerateCity() {
    // clean the old scene first:
    m_building_arr.clear();

    // make the ground plane:
    glm::mat4 groundCTM = glm::mat4(1.0f);
    groundCTM = glm::scale(groundCTM, glm::vec3(40.0f, 0.001f, 40.0f));
    m_CTM_collection.push_back(groundCTM);

    // add some streets in the city:
    Building street1(glm::vec3(0.0f, 0.0f, 2.0f),glm::vec3(40.0f, 0.02f, 0.5f));
    Building street2(glm::vec3(0.0f, 0.0f, -5.0f),glm::vec3(40.0f, 0.02f, 0.7f));
    Building street3(glm::vec3(-5.0f, 0.0f, 0.0f),glm::vec3(0.7f, 0.02f, 40.0f));
    Building street4(glm::vec3(3.0f, 0.0f, 0.0f),glm::vec3(0.7f, 0.02f, 40.0f));
    Building street5(glm::vec3(7.0f, 0.0f, 0.0f),glm::vec3(0.5f, 0.02f, 40.0f));
    Building street6(glm::vec3(0.0f, 0.0f, 8.0f),glm::vec3(40.0f, 0.02f, 0.5f));
    Building street7(glm::vec3(0.0f, 0.0f, -12.0f),glm::vec3(40.0f, 0.02f, 0.7f));
    Building street8(glm::vec3(0.0f, 0.0f, -17.0f),glm::vec3(40.0f, 0.02f, 0.7f));
    Building street9(glm::vec3(-12.0f, 0.0f, 0.0f),glm::vec3(0.7f, 0.02f, 40.0f));
    Building street0(glm::vec3(15.0f, 0.0f, 0.0f),glm::vec3(0.5f, 0.02f, 40.0f));
    m_building_arr.push_back(street1);
    m_building_arr.push_back(street2);
    m_building_arr.push_back(street3);
    m_building_arr.push_back(street4);
    m_building_arr.push_back(street5);
    m_building_arr.push_back(street6);
    m_building_arr.push_back(street7);
    m_building_arr.push_back(street8);
    m_building_arr.push_back(street9);
    m_building_arr.push_back(street0);

    // add some random cubes:
    int overlapCounter = 0;
    // if the random building generator tries X times and still overalps with some buildings,
    // then the city might be too crowded, we should stop adding new Buildings
    int overlapThreshold = 100;
    for(int i = 0; i < 240;){
        float random_scale_x = getRandomFloat(0.8f, 1.5f);
        float random_scale_y = getRandomFloat(1.0f, 3.5f);
        float random_scale_z = getRandomFloat(0.8f, 1.5f);
        float random_x = getRandomFloat(-18.0f,18.0f);
        float random_z = getRandomFloat(-18.0f,18.0f);
        float y = 0.5f*random_scale_y;
        glm::vec3 scale(random_scale_x,random_scale_y,random_scale_z);
        glm::vec3 pos(random_x, y, random_z);
        Building newBuilding(pos, scale);
        bool overlapFound = false;
        for(Building b : m_building_arr){
            if(newBuilding.checkOverlap(b)){
                overlapFound = true;
                overlapCounter++; // increment the overlap counter
                break;
            }
        }

        if(overlapFound && overlapCounter >= overlapThreshold){
            std::cout<<"The city is too crowded! Stop adding new buildings!"<<std::endl;
            break; // Break out of the loop if the overlap threshold is reached
        }

        if(!overlapFound){
            m_building_arr.push_back(newBuilding);
            i++;
            overlapCounter = 0; // Reset overlap counter after successful addition
        }
    }
}





void Realtime::finish() {
    killTimer(m_timer);
    this->makeCurrent();


    // Students: anything requiring OpenGL calls when the program exits should be done here

    //TO DO: HOW TO GENERALIZE THIS TO WORK ON THE DIFFERENT m-VAOS and m_sphere_vboS
    glDeleteBuffers(1, &m_sphere_vbo);
    glDeleteVertexArrays(1, &m_sphere_vao);

    glDeleteBuffers(1, &m_cube_vbo);
    glDeleteVertexArrays(1, &m_cube_vao);

    glDeleteBuffers(1, &m_cone_vbo);
    glDeleteVertexArrays(1, &m_cone_vao);

    glDeleteBuffers(1, &m_cylinder_vbo);
    glDeleteVertexArrays(1, &m_cylinder_vao);

    glDeleteProgram(m_shader);

    this->doneCurrent();
}

void Realtime::getData(){
    sphere tempSphere = sphere();
    templateSphereData = tempSphere.generateShape();



}

void verifyVAO(std::vector<GLfloat> &triangleData, GLuint index, GLsizei size, GLsizei stride, const void* offset) {

    int newStride = int(stride / 4);
    int groupNum = 0;
    int newOffset = static_cast<int>(reinterpret_cast<intptr_t>(offset)) / 4;

    for (int i = newOffset; i < triangleData.size(); i = i + newStride) {
        std::cout << "Group " << groupNum << " of Values for VAO index " << index << std::endl;
        std::cout << "[";
        for (auto j = i; j < i + size; ++j) {
            if (j != i + size - 1) {
                std::cout << triangleData[j]<< ", ";
            } else {
                std::cout << triangleData[j]<< "]" << std::endl;
            }
        }
        groupNum = groupNum + 1;
    }
    std::cout << "" << std::endl;
}

//void Realtime::GlBinder(){

//}

void Realtime::binderHelper(GLuint VAO, GLuint VBO, std::vector<float> vertexData/* PrimitiveType shapeType*/){
    //    makeCurrent();

    //glGenBuffers(1, &m_sphere_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Generate sphere data
    //templateSphereData = generateSphereData(10,20);




    // Send data to VBO
    glBufferData(GL_ARRAY_BUFFER,vertexData.size() * sizeof(GLfloat),vertexData.data(), GL_STATIC_DRAW);
    // Generate, and bind vao
    //glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Enable and define attribute 0 to store vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6 * sizeof(GLfloat),reinterpret_cast<void *>(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));



    // Clean-up bindings
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);


}

void Realtime::insertVec3(std::vector<float> &data, glm::vec3 v) {
    data.push_back(v.x);
    data.push_back(v.y);
    data.push_back(v.z);
}

void Realtime::generateData(){

    tempSphere = sphere();
    tempSphere.updateParams(settings.shapeParameter1, settings.shapeParameter2);
    templateSphereData = tempSphere.generateShape();
    // std::cout<< templateSphereData.size() << std::endl;

    tempCube = cube();
    tempCube.updateParams(settings.shapeParameter1);
    templateCubeData = tempCube.generateShape();

    tempCylinder = cylinder();
    tempCylinder.updateParams(settings.shapeParameter1, settings.shapeParameter2);
    templateCylinderData = tempCylinder.generateShape();

    tempCone = cone();
    tempCone.updateParams(settings.shapeParameter1);
    templateConeData = tempCone.generateShape(true);

    tempSnow = snow();
    tempSnow.snowMaker(0.01f, 100, m_screen_width, m_screen_height);
    m_snowData = tempSnow.generateShape();



}

void Realtime::addParticle(float x, float y, float z, int ind){
    Particle particle = Particle{glm::vec3(x,y,z)};
    particle.index = ind;
    particles.push_back(particle);
    //std::cout << "particle added succesfully" << std::endl;


}

//void Realtime::removeParticle(int i){
//    int del = particles.begin() + i;
//    particles.erase(del);
//}

//void Realtime::populate


void Realtime::initializeGL() {
    settingsCalled = true;
    m_devicePixelRatio = this->devicePixelRatio();

    m_defaultFBO = 2;
    m_screen_width = size().width() * m_devicePixelRatio;
    m_screen_height = size().height() * m_devicePixelRatio;
    m_fbo_width = m_screen_width;  //LAB11
    m_fbo_height = m_screen_height; //LAB11

    m_timer = startTimer(1000/60);
    m_elapsedTimer.start();

    //std::cout << "Do not go gentle into that good night, Old age should burn and rave at close of day; Rage, rage against the dying of the light. Though wise men at their end know dark is right, Because their words had forked no lightning they Do not go gentle into that good night. Good men, the last wave by, crying how bright Their frail deeds might have danced in a green bay, Rage, rage against the dying of the light. Wild men who caught and sang the sun in flight, And learn, too late, they grieved it on its way, Do not go gentle into that good night. Grave men, near death, who see with blinding sight Blind eyes could blaze like meteors and be gay, Rage, rage against the dying of the light. And you, my father, there on the sad height, Curse, bless, me now with your fierce tears, I pray. Do not go gentle into that good night. Rage, rage against the dying of the light. " <<std::endl;

    //    camera = Cam(metaData.cameraData, size().width(), size().height(), settings.nearPlane, settings.farPlane);
    //    m_view = camera.getViewMatrix();
    //    m_proj = camera.getProjectMatrix();

    // Initializing GL.
    // GLEW (GL Extension Wrangler) provides access to OpenGL functions.
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Error while initializing GL: " << glewGetErrorString(err) << std::endl;
    }
    std::cout << "Initialized GL: Version " << glewGetString(GLEW_VERSION) << std::endl;

    // Allows OpenGL to draw objects appropriately on top of one another
    glEnable(GL_DEPTH_TEST);
    // Tells OpenGL to only draw the front face
    glEnable(GL_CULL_FACE);
    // Tells OpenGL how big the screen is
    glViewport(0, 0, size().width() * m_devicePixelRatio, size().height() * m_devicePixelRatio); // LAB11 Difference

    // Students: anything requiring OpenGL calls when the program starts should be done here

    //set bg color; reference lab 9
    glClearColor(0.f, 0.f, 0.f, 1.f);


    for(int i = 0; i < numberOfParticles; i++){
        float xOffset = -1.f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.f-(-1.f))));
        float yOffset = -1.f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.f-(-1.f))));
        float zOffset = 0.f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.f-(0.f))));


        addParticle(xOffset, yOffset, zOffset, i);



    }

    //    for(int i = 0; i < particles.size(); i++){
    //        std::cout << particles[i].index << std::endl;
    //    }



    //Shader set up
    m_texture_shader = ShaderLoader::createShaderProgram(":/resources/shaders/texture.vert", ":/resources/shaders/texture.frag"); // LAB11 Difference

    m_shader = ShaderLoader::createShaderProgram(":/resources/shaders/default.vert", ":/resources/shaders/default.frag");

    m_hdr_shader =  ShaderLoader::createShaderProgram(":/resources/shaders/hdr.vert", ":/resources/shaders/hdr.frag");


    //QString kitten_filepath = QString(":/resources/kitten.png");

    //    // LAB11 TASK 1-10
    //    m_image = QImage(kitten_filepath);
    //    // Task 2: Format image to fit OpenGL
    //    m_image = m_image.convertToFormat(QImage::Format_RGBA8888).mirrored();



    // Task 10: Set the texture.frag uniform for our texture
    // ALso passes in screen height and width for sampling purposes
    glUseProgram(m_texture_shader);
    GLint location = glGetUniformLocation(m_texture_shader, "text");
    glUniform1i(location, 0);
    GLint locationScreenWidth = glGetUniformLocation(m_texture_shader, "screenW");
    glUniform1i(locationScreenWidth, m_screen_width);
    GLint locationScreenHeight = glGetUniformLocation(m_texture_shader, "screenH");
    glUniform1i(locationScreenHeight, m_screen_height);

    glUseProgram(0);

    glUseProgram(m_hdr_shader);
    GLint hdrLoc = glGetUniformLocation(m_hdr_shader, "hdr_texture");
    glUniform1i(location, 0);
    glUseProgram(0);

    //    glUseProgram(m_hdr_shader);
    //    GLint snowLoc = glGetUniformLocation(m_hdr_shader, "snowText");
    //    glUniform1i(location, 0);
    //    glUseProgram(0);

    std::vector<GLfloat> fullscreen_quad_data =
        { //     POSITIONS    //
            -1.f,  1.f, 0.f, 0.f, 1.f,
            -1.f, -1.f, 0.f, 0.f, 0.f,
            1.f, -1.f, 0.f, 1.f, 0.f,
            1.f,  1.f, 0.f, 1.f, 1.f,
            -1.f,  1.f, 0.f, 0.f, 1.f,
            1.f, -1.f, 0.f, 1.f, 0.f,

            //            -0.2,  0.2, 0.f, 0.f, 0.2,
            //            -0.2, -0.2, 0.f, 0.f, 0.f,
            //            0.2, -0.2, 0.f, 0.2, 0.f,
            //            0.2,  0.2, 0.f, 0.2, 0.2,
            //            -0.2,  0.2, 0.f, 0.f, 0.2,
            //            0.2, -0.2, 0.f, 0.2, 0.f,

            //            -0.4,  0.4, 0.f, 0.f, 0.2,
            //            -0.4, -0.4, 0.f, 0.f, 0.f,
            //            0.4, -0.4, 0.f, 0.2, 0.f,
            //            0.4,  0.4, 0.f, 0.2, 0.2,
            //            -0.4,  0.4, 0.f, 0.f, 0.2,
            //            0.4, -0.4, 0.f, 0.2, 0.f
        };

    // Generate and bind a VBO and a VAO for a fullscreen quad
    glGenBuffers(1, &m_fullscreen_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_fullscreen_vbo);
    glBufferData(GL_ARRAY_BUFFER, fullscreen_quad_data.size()*sizeof(GLfloat), fullscreen_quad_data.data(), GL_STATIC_DRAW);
    glGenVertexArrays(1, &m_fullscreen_vao);
    glBindVertexArray(m_fullscreen_vao);


    // Task 14: modify the code below to add a second attribute to the vertex attribute array
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));

    // Unbind the fullscreen quad's VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //makeFBO TODO


    //INITIALIZING TEMPLATE SHAPES
    generateData();

    glGenBuffers(1, &m_sphere_vbo);
    glGenVertexArrays(1, &m_sphere_vao);
    binderHelper(m_sphere_vao, m_sphere_vbo, templateSphereData);

    glGenBuffers(1, &m_cube_vbo);
    glGenVertexArrays(1, &m_cube_vao);
    binderHelper(m_cube_vao, m_cube_vbo, templateCubeData);

    glGenBuffers(1, &m_cylinder_vbo);
    glGenVertexArrays(1, &m_cylinder_vao);
    binderHelper(m_cylinder_vao, m_cylinder_vbo, templateCylinderData);

    glGenBuffers(1, &m_cone_vbo);
    glGenVertexArrays(1, &m_cone_vao);
    binderHelper(m_cone_vao, m_cone_vbo, templateConeData);

    glGenBuffers(1, &m_snow_vbo);
    glGenVertexArrays(1, &m_snow_vao);
    //    binderHelper(m_snow_vao, m_snow_vbo, m_snowData);
    glGenBuffers(1, &m_snow_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_snow_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_snowData.size()*sizeof(GLfloat), m_snowData.data(), GL_STATIC_DRAW);
    glGenVertexArrays(1, &m_snow_vao);
    glBindVertexArray(m_snow_vao);


    // Task 14: modify the code below to add a second attribute to the vertex attribute array
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));

    // Unbind the fullscreen quad's VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);













    //verifyVAO(m_snowData, 0, 3, 5 * sizeof(GL_FLOAT), reinterpret_cast<void*>(0));

    //    for(int i = 0; i < m_snowData.size(); i++){
    //        std::cout<< m_snowData[i] << std::endl;
    //    }

    //makeHdrFBO();
    makeFBO();

    //for final project
    GenerateCity();

}

//void Realtime::snowMaker(float size, float maxParticles){
//    std::vector<float> snowSystem;


//    for(int i = 0; i <= maxParticles; i++){
//        int xRandomizer = i * rand() % m_screen_width;
//        int yRandomizer = i * rand() % m_screen_height;

//        std::vector<float> snowData =
//            { //     POSITIONS    //
//                -size * xRandomizer,  size * yRandomizer, 0.f, 0.f, size,
//                -size * xRandomizer, -size * yRandomizer, 0.f, 0.f, 0.f,
//                size * xRandomizer, -size * yRandomizer, 0.f, size, 0.f,
//                size * xRandomizer,  size * yRandomizer, 0.f, size, size,
//                -size * xRandomizer,  size * yRandomizer, 0.f, 0.f, size,
//                size * xRandomizer, -size * yRandomizer, 0.f, size, 0.f
//            };

//        snowSystem.push_back(snowData);




//    }


//}

void Realtime::makeFBO(){
    glGenTextures(1, &m_new_fbo_texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_new_fbo_texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_fbo_width, m_fbo_height, 0, GL_RGBA, GL_FLOAT, nullptr);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);//FINALCHANGE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);//FINALCHANGE

    glBindTexture(GL_TEXTURE_2D, 0);

    //trying second texture
    glGenTextures(1, &m_hdr_fbo_texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_hdr_fbo_texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_fbo_width, m_fbo_height, 0, GL_RGBA, GL_FLOAT, nullptr);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);//FINALCHANGE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);//FINALCHANGE

    glBindTexture(GL_TEXTURE_2D, 0);



    // Task 20: Generate and bind a renderbuffer of the right size, set its format, then unbind
    glGenRenderbuffers(1, &m_new_fbo_renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_new_fbo_renderbuffer);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_fbo_width, m_fbo_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);


    // Task 18: Generate and bind an FBO
    glGenFramebuffers(1, &m_new_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_new_fbo);

    // Task 21: Add our texture as a color attachment, and our renderbuffer as a depth+stencil attachment, to our FBO
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_new_fbo_texture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_hdr_fbo_texture, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_new_fbo_renderbuffer);
    // Task 22: Unbind the FBO
    glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFBO);

    //Trying to work with two FBOs
    //glGenFramebuffers(1, &m_hdr_fbo);             //ERROR HAPPENS HERE, generating FBO FUCKS US UP

    //    glBindFramebuffer(GL_FRAMEBUFFER, m_hdr_fbo);//generating hdr fbo

    //Generating new textures
    //    glGenTextures(1, &m_hdr_fbo_texture);
    //    glBindTexture(GL_TEXTURE_2D, m_hdr_fbo_texture);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);//FINALCHANGE
    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);//FINALCHANGE

    //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_fbo_width, m_fbo_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    //    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_hdr_fbo_texture, 0);
    //    glBindTexture(GL_TEXTURE_2D, 0);
    //    glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFBO);



}

void Realtime::snowBinder(){
    glGenTextures(1, &m_hdr_fbo_texture);
    glBindTexture(GL_TEXTURE_2D, m_hdr_fbo_texture);


}

void Realtime::makeHdrFBO(){
    glGenTextures(1, &m_hdr_fbo_texture);
    glActiveTexture(GL_TEXTURE1);//look into
    glBindTexture(GL_TEXTURE_2D, m_hdr_fbo_texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_fbo_width, m_fbo_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);



    // Task 20: Generate and bind a renderbuffer of the right size, set its format, then unbind
    glGenRenderbuffers(1, &m_hdr_fbo_renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_hdr_fbo_renderbuffer);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_fbo_width, m_fbo_height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);


    // Task 18: Generate and bind an FBO
    glGenFramebuffers(1, &m_hdr_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_hdr_fbo);

    // Task 21: Add our texture as a color attachment, and our renderbuffer as a depth+stencil attachment, to our FBO
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_hdr_fbo_texture, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_hdr_fbo_renderbuffer);
    // Task 22: Unbind the FBO
    glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFBO);


}

//MAKE IT WORK FOR ALL LIGHTS AND STRUCTS
void Realtime::lightsHelper(std::vector<SceneLightData> lights, GLuint shader){
    //std::cout << "dirrHelperCalled " << std::endl;
    for(int i = 0; i < metaData.lights.size(); i++){
        //if(metaData.lights[i].type == LightType::LIGHT_DIRECTIONAL){

        std::string s = "lights[" + std::to_string(i) + "].type"; //look into implementing multiple lights
        GLint locType = glGetUniformLocation(shader, s.c_str());

        std::string sCol = "lights[" + std::to_string(i) + "].color"; //look into implementing multiple lights
        GLint locColor = glGetUniformLocation(shader, sCol.c_str());
        glUniform3fv(locColor, 1, &lights[i].color[0]);

        std::string sAtt = "lights[" + std::to_string(i) + "].attenuation"; //look into implementing multiple lights
        GLint locAtt = glGetUniformLocation(shader, sAtt.c_str());

        std::string sPos = "lights[" + std::to_string(i) + "].pos"; //look into implementing multiple lights
        GLint locPos = glGetUniformLocation(shader, sPos.c_str());

        std::string sDir = "lights[" + std::to_string(i) + "].dir"; //look into implementing multiple lights
        GLint locDir = glGetUniformLocation(shader, sDir.c_str());

        std::string sPen = "lights[" + std::to_string(i) + "].penumbra"; //look into implementing multiple lights
        GLint locPen = glGetUniformLocation(shader, sPen.c_str());

        std::string sAng = "lights[" + std::to_string(i) + "].angle"; //look into implementing multiple lights
        GLint locAng = glGetUniformLocation(shader, sAng.c_str());

        glm::vec3 nullVec(0.f);

        //************************************************************************
        switch(lights[i].type){
        case LightType::LIGHT_DIRECTIONAL: {
            glUniform1i(locType, 0);
            glUniform1f(locAng, 0.f);
            glUniform1f(locPen, 0.f);
            glUniform3fv(locDir, 1, &lights[i].dir[0]);
            glUniform3fv(locPos, 1, &nullVec[0]);
            glUniform3fv(locAtt, 1, &nullVec[0]);

            break;
        }
        case LightType::LIGHT_POINT: {
            glUniform1i(locType, 1);
            glUniform1f(locAng, 0.f);
            glUniform1f(locPen, 0.f);
            glUniform3fv(locDir, 1, &nullVec[0]);
            glUniform3fv(locPos, 1, &lights[i].pos[0]);
            glUniform3fv(locAtt, 1, &lights[i].function[0]);

            break;
        }
        case LightType::LIGHT_SPOT: {
            glUniform1i(locType, 2);
            glUniform1f(locAng, lights[i].angle);
            glUniform1f(locPen, lights[i].penumbra);
            glUniform3fv(locDir, 1, &lights[i].dir[0]);
            glUniform3fv(locPos, 1, &lights[i].pos[0]);
            glUniform3fv(locAtt, 1, &lights[i].function[0]);

            break;
        }
        }


    }
}


//DO AWAY WITH
void Realtime::lightsColorHelper(std::vector<SceneLightData> lights, GLuint shader){
    // std::cout << "colorHelperCalled " << std::endl;
    for(int i = 0; i < metaData.lights.size(); i++){
        if(metaData.lights[i].type == LightType::LIGHT_DIRECTIONAL){

            std::string s = "lightColors[" + std::to_string(i) + "]";
            GLint loc = glGetUniformLocation(shader, s.c_str());
            glUniform3fv(loc, 1, &lights[i].color[0]);

        }
    }
}


int Realtime::getNumberOfLights(std::vector<SceneLightData> lights){
    int result = 0;
    for(int i = 0; i < lights.size(); i++){

        result++;

    }
    return result;
}

void glErrorCheck(){
    GLenum error = glGetError();
    while(error != GL_NO_ERROR){
        std::cout<<error<<std::endl;

        error = glGetError();
    }
}


void Realtime::paintGL() {
    // Students: anything requiring OpenGL calls every frame should be done here

    //Binding newFbo
    glBindFramebuffer(GL_FRAMEBUFFER, m_new_fbo);
    //std::cout<<  "m_new_fbo" << m_new_fbo << std::endl;
    //VIEWPORT STUFF
    glViewport(0,0,  m_fbo_width,  m_fbo_height);
    //CLEAR COLOR STUFF FOR DEBUGGING


    //FOR LAB11 THIS IS WHERE PAINTEXAMPLE GEOMETRY BEGINS
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    particleRemover();
    for(int i = 0; i < particles.size(); i++){

        paintSnow(m_new_fbo_texture, m_view, m_proj, glm::vec3(0.7f, 0.7f, 0.7f), particles[i]);
    }

    glBindTexture(GL_TEXTURE_2D, m_hdr_fbo_texture);
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, m_fbo_width, m_fbo_height);
    glBindTexture(GL_TEXTURE_2D, 0);

    //NORMAL CODE BEGINS
    glUseProgram(m_shader);

    //setting texture



    //for(int i = 0; i < metaData.shapes.size(); i++){


    // Bind the shader
    //camera = Cam(metaData.cameraData, projWidth, projHeight, settings.nearPlane, settings.farPlane);
    m_view = camera.getViewMatrix();
    m_proj = camera.getProjectMatrix();

    //Delegate to a helper for generating lights







     //if(metaData.shapes.size() != 0){
        // ****TO DO: PASS IN MODEL MATRIX AS UNIFORM
        // PASS IN ALL YOUR UNIFORMS
        for(int i = 0; i < metaData.shapes.size(); i++){
            float triangles;

            switch (metaData.shapes[i].primitive.type) {
            case PrimitiveType::PRIMITIVE_CUBE:
                glBindVertexArray(m_cube_vao);
                triangles = templateCubeData.size()/6;
                break;
            case PrimitiveType::PRIMITIVE_SPHERE:
                glBindVertexArray(m_sphere_vao);
                triangles = templateSphereData.size()/6;

                break;
            case PrimitiveType::PRIMITIVE_CYLINDER:
                glBindVertexArray(m_cylinder_vao); //FIX THIS
                triangles = templateCylinderData.size()/6;//FIX THIS

                break;
            case PrimitiveType::PRIMITIVE_CONE:
                glBindVertexArray(m_cone_vao); //FIX THIS
                triangles = templateConeData.size()/6;//FIX THIS

                break;
            case PrimitiveType::PRIMITIVE_MESH:
                glBindVertexArray(m_sphere_vao); //FIX THIS

                break;
            }


            GLint modelMatlocation = glGetUniformLocation(m_shader, "modelMat");
            glUniformMatrix4fv(modelMatlocation, 1, GL_FALSE, /*&m_modelTest[0][0]*/&metaData.shapes[i].ctm[0][0]);// using metadata causes program to crash

            GLint viewMatLocation = glGetUniformLocation(m_shader, "viewMat");
            glUniformMatrix4fv(viewMatLocation, 1, GL_FALSE, &m_view[0][0]); //passing in the right matrix messes stuff up

            GLint projMatLocation = glGetUniformLocation(m_shader, "projMat");
            glUniformMatrix4fv(projMatLocation, 1, GL_FALSE, &m_proj[0][0]); //passing in the right matrix messes stuff up

            GLint locationAmb = glGetUniformLocation(m_shader, "k_A");
            glUniform1f(locationAmb, metaData.globalData.ka);

            GLint locationDif = glGetUniformLocation(m_shader, "k_D");
            glUniform1f(locationDif, metaData.globalData.kd);

            GLint locationSpec = glGetUniformLocation(m_shader, "k_S");
            glUniform1f(locationSpec, metaData.globalData.ks);

            //            metaData.cameraData.pos

            glm::vec4 camPos = glm::inverse(m_view) * metaData.cameraData.pos;
            GLint locationCameraPos = glGetUniformLocation(m_shader, "cameraPos");
            glUniform4fv(locationCameraPos, 1 , &camPos[0]);

            GLint shineLoc = glGetUniformLocation(m_shader, "shine");
            glUniform1f(shineLoc , metaData.shapes[i].primitive.material.shininess);


            // Multiple light stuff
            int lightSize = getNumberOfLights(metaData.lights) + m_building_arr.size();


            //Now make this work for all lights
            //Passing actual data into the structs
            lightsHelper(metaData.lights, m_shader);//888 MAJOR CHANGES HERE
            lightsColorHelper(metaData.lights, m_shader);//888 MAJOR CHANGES HERE

            //std::cout<< lightDirSize << std::endl;
            GLint locationArraySize = glGetUniformLocation(m_shader, "arraySize");
            glUniform1i(locationArraySize, lightSize);

            //end multiple light stuff


            // std::cout << metaData.shapes[2].primitive.material.cAmbient[0] << metaData.shapes[2].primitive.material.cAmbient[1] << metaData.shapes[2].primitive.material.cAmbient[2] <<std::endl;
            GLint ambientColorLoc = glGetUniformLocation(m_shader, "m_A");
            glUniform3fv(ambientColorLoc, 1, &metaData.shapes[i].primitive.material.cAmbient[0]);

            GLint specularColorLoc = glGetUniformLocation(m_shader, "m_S");
            glUniform3fv(specularColorLoc, 1, &metaData.shapes[i].primitive.material.cSpecular[0]);

            GLint diffuseColorLoc = glGetUniformLocation(m_shader, "m_D");
            glUniform3fv(diffuseColorLoc, 1, &metaData.shapes[i].primitive.material.cDiffuse[0]);

            glDrawArrays(GL_TRIANGLES, 0, triangles);
            glBindVertexArray(0);

            // -----------final project part---------------------//

            // paint the ground plain:
            glm::mat4 groundCTM = m_CTM_collection[0];
            glm::vec4 Ambient = glm::vec4(1.0,1.0,1.0,0.0);
            glm::vec4 Diffuse = glm::vec4(0.7,0.7,0.7,0.0);
            // glm::vec4 Specular = glm::vec4(1.0,1.0,1.0,0.0);
            GLint locationM = glGetUniformLocation(m_shader,"modelMat");
            glUniformMatrix4fv(locationM,1,GL_FALSE,&groundCTM[0][0]);
            GLint locations = glGetUniformLocation(m_shader,"shine");
            glUniform1f(locations,15);
            GLint locationcA = glGetUniformLocation(m_shader,"m_A");
            // glUniform4fv(locationcA,1,&Ambient[0]);
            GLint locationcD = glGetUniformLocation(m_shader,"m_D");
            glUniform4fv(locationcD,1,&Diffuse[0]);
            GLint locationcS = glGetUniformLocation(m_shader,"m_S");
            // glUniform4fv(locationcS,1,&Specular[0]);
            glBindVertexArray(m_cube_vao);
            triangles = templateCubeData.size()/6;
            glDrawArrays(GL_TRIANGLES, 0, triangles);
            glBindVertexArray(0);


            // paint the street:
            for(int i = 0; i < 5; i++){
                glm::mat4 CTM = m_building_arr[i].CTM;
                glm::vec4 Ambient = glm::vec4(0.0,0.5,0.5,0.0);
                glm::vec4 Diffuse = glm::vec4(0.0,0.7,0.7,0.0);
                // glm::vec4 Specular = glm::vec4(1.0,1.0,1.0,1.0);
                GLint locationM = glGetUniformLocation(m_shader,"modelM");
                glUniformMatrix4fv(locationM,1,GL_FALSE,&CTM[0][0]);
                glm::mat4 MVP = m_proj * m_view * CTM;
                GLint locationMVP = glGetUniformLocation(m_shader, "MVP");
                glUniformMatrix4fv(locationMVP,1,GL_FALSE,&MVP[0][0]);
                GLint locations = glGetUniformLocation(m_shader,"shine");
                glUniform1f(locations,0);
                GLint locationcA = glGetUniformLocation(m_shader,"m_A");
                glUniform4fv(locationcA,1,&Ambient[0]);
                GLint locationcD = glGetUniformLocation(m_shader,"m_D");
                glUniform4fv(locationcD,1,&Diffuse[0]);
                //            GLint locationcS = glGetUniformLocation(m_shader,"m_S");
                //            glUniform4fv(locationcS,1,&Specular[0]);
                glBindVertexArray(m_cube_vao);
                triangles = templateCubeData.size()/6;
                glDrawArrays(GL_TRIANGLES, 0, triangles);
                glBindVertexArray(0);
            }

            // generate a light within each bulding
            int lightStart = metaData.lights.size();
            int building_index = 0;
            glm::vec3 nullVec = glm::vec3(0.0, 0.0, 0.0);
            glm::vec3 color = glm::vec3(0.5, 0.5, 0.25);
            glm::vec3 atten = glm::vec3(0.05, 0.8, 2.0);
            for (int i = lightStart; i < (m_building_arr.size() + lightStart); i++) {
                // get current buliding ctm
                // use to generate a light position



                glm::vec3 position(m_building_arr[i].position[0] + 0.3, m_building_arr[i].position[1] - 1.f, m_building_arr[i].position[2] - 0.3);


                std::string s = "lights[" + std::to_string(i) + "].type"; //look into implementing multiple lights
                GLint locType = glGetUniformLocation(m_shader, s.c_str());

                std::string sCol = "lights[" + std::to_string(i) + "].color"; //look into implementing multiple lights
                GLint locColor = glGetUniformLocation(m_shader, sCol.c_str());

                std::string sAtt = "lights[" + std::to_string(i) + "].attenuation"; //look into implementing multiple lights
                GLint locAtt = glGetUniformLocation(m_shader, sAtt.c_str());

                std::string sPos = "lights[" + std::to_string(i) + "].pos"; //look into implementing multiple lights
                GLint locPos = glGetUniformLocation(m_shader, sPos.c_str());

                std::string sDir = "lights[" + std::to_string(i) + "].dir"; //look into implementing multiple lights
                GLint locDir = glGetUniformLocation(m_shader, sDir.c_str());

                std::string sPen = "lights[" + std::to_string(i) + "].penumbra"; //look into implementing multiple lights
                GLint locPen = glGetUniformLocation(m_shader, sPen.c_str());

                std::string sAng = "lights[" + std::to_string(i) + "].angle"; //look into implementing multiple lights
                GLint locAng = glGetUniformLocation(m_shader, sAng.c_str());

                //position = glm::vec3(1.f, 1.f, 1.f);


                glUniform1i(locType, 1);


                glUniform1f(locAng, 0.f);


                glUniform1f(locPen, 0.f);

                glUniform3fv(locDir, 1, &nullVec[0]);



                glUniform3fv(locColor, 1, &color[0]);



                glUniform3fv(locAtt, 1, &atten[0]);



                glUniform3fv(locPos, 1, &position[0]);




                building_index++;
            }

            // paint all the buildings
            for(int i = 0; i < m_building_arr.size(); i++){
                glm::mat4 CTM = m_building_arr[i].CTM;
                glm::vec4 Ambient = glm::vec4(0.5,0.5,0.5,0.0);
                glm::vec4 Diffuse = glm::vec4(0.7,0.7,0.5,0.0);
                glm::vec4 Specular = glm::vec4(0.2,0.2,0.2,1.0);
                GLint locationM = glGetUniformLocation(m_shader,"modelMat");
                glUniformMatrix4fv(locationM,1,GL_FALSE,&CTM[0][0]);
                GLint locations = glGetUniformLocation(m_shader,"shine");
                glUniform1f(locations,0);
                GLint locationcA = glGetUniformLocation(m_shader,"m_A");
                glUniform4fv(locationcA,1,&Ambient[0]);
                GLint locationcD = glGetUniformLocation(m_shader,"m_D");
                glUniform4fv(locationcD,1,&Diffuse[0]);
                GLint locationcS = glGetUniformLocation(m_shader,"m_S");
                glUniform4fv(locationcS,1,&Specular[0]);

                float r = m_building_arr[i].randy;
                if (r < 0.5) {
                    glBindVertexArray(m_cube_vao);
                    triangles = templateCubeData.size()/6;
                    glDrawArrays(GL_TRIANGLES, 0, triangles);
                } else if (r < 0.75) {
                    glBindVertexArray(m_cylinder_vao);
                    triangles = templateCylinderData.size()/6;
                    glDrawArrays(GL_TRIANGLES, 0, triangles);
                } else {
                    glBindVertexArray(m_cone_vao);
                    triangles = templateConeData.size()/6;
                    glDrawArrays(GL_TRIANGLES, 0, triangles);
                }
                glBindVertexArray(0);



            }
            // ----------final project-----------------------//



        }
    // }

    // Unbind the shader
    glUseProgram(0);


    //TRYING TO MAKE TWO FBOS WORK TOGETHER
    //    glBindFramebuffer(GL_FRAMEBUFFER, m_hdr_fbo);
    //    //std::cout<<  "m_new_fbo" << m_new_fbo << std::endl;
    //    //VIEWPORT STUFF
    //    glViewport(0,0,  m_fbo_width,  m_fbo_height);

    //    glActiveTexture(GL_TEXTURE1);
    //    glBindTexture(GL_TEXTURE_2D, m_hdr_fbo_texture);
    //            particleRemover();
    //        for(int i = 0; i < particles.size(); i++){

    //            paintSnow(m_hdr_shader, m_view, m_proj, glm::vec3(0.7f, 0.7f, 0.7f), particles[i]);
    //        }


    //NORMAL CODE ENDS
    //    paintSnow(m_texture_shader);






    //FOR LAB11 THIS IS WHERE PAINTEXAMPLE GEOMETRY ENDS

    //    makeHdrFBO();

    glBindFramebuffer(GL_FRAMEBUFFER, m_defaultFBO);
    //glBindFramebuffer(GL_FRAMEBUFFER, m_new_fbo);
    //std::cout<<  "m_hdr_fbo" << m_hdr_fbo << std::endl;
    //VIEWPORT STUFF
    glViewport(0,0, m_screen_width, m_screen_height);
    // CLEAR COLOR STUFF FOR DEBUGGING

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Calling Texture now

    int filterType = 0;
    if(settings.perPixelFilter){
        filterType = 1;
    }

    if(settings.kernelBasedFilter){
        filterType = 2;
    }


     paintTexture(m_new_fbo_texture, filterType);





}

void Realtime::paintTexture(GLuint texture, int process){
    glUseProgram(m_texture_shader);
    // Task 32: Set your bool uniform on whether or not to filter the texture drawn
    //glGetUniformLocation(m_texture_shader, "inverter");
    //glUniform1i(glGetUniformLocation(m_texture_shader, "inverter"), process);

    glBindVertexArray(m_fullscreen_vao);
    // Task 10: Bind "texture" to slot 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);


    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

glm::mat4 translator(float dx, float dy, float dz){
    return glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, dx, dy, dz, 1);
}

void Realtime::particleRemover(){
    //Removes particles and (adds new Ones?)


    std::sort(particles.begin(), particles.end(), particle);

    //    if(particles.end()->isAlive == 0){
    //        particles.pop_back();
    //        float xOffset = -1.f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.f-(-1.f))));
    //        float yOffset = -1.f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.f-(-1.f))));
    //        float zOffset = 0.f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.f-(0.f))));
    //        //particles.begin()


    //        addParticle(xOffset, yOffset, zOffset, particles.size()-1);
    //    }

    for(int i = 0; i < particles.size(); i++){
        if(particles[i].isAlive == 0){
            particles.pop_back();
            float xOffset = -1.f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.f-(-1.f))));
            float yOffset = -1.f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.f-(-1.f))));
            float zOffset = 0.f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.f-(0.f))));
            //particles.begin()


            addParticle(xOffset, -1.0f, zOffset, particles.size()-1);
        }

    }






}

void Realtime::paintSnow(GLuint texture, glm::mat4 view, glm::mat4 proj, glm::vec3 offset, Particle currPart){
    bool isDissolved = false;
    //    if(currPart.lifetime <= 0){
    //    //currPart.offset[1] = 0.6f;
    //    //currPart.particleIncrementor = 0.f;
    //    //currPart.lifetime = 200/pow(currPart.offset[2],2);
    //    isDissolved = true;
    //    float xOffset = -1.f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.f-(-1.f))));
    //    float yOffset = -1.f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.f-(-1.f))));
    //    float zOffset = 0.f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.f-(0.f))));
    //    //particles.begin()


    //   // addParticle(xOffset, yOffset, zOffset);
    //    //addParticle(currPart.offset)

    //    }

    glUseProgram(m_hdr_shader);
    // Task 32: Set your bool uniform on whether or not to filter the texture drawn
    //glGetUniformLocation(m_texture_shader, "inverter");
    //glUniform1i(glGetUniformLocation(m_texture_shader, "inverter"), process);

    glBindVertexArray(m_snow_vao);
    // Task 10: Bind "texture" to slot 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glm::mat4 translate = translator(1.f, 1.1f, 1.f);
    glm::mat4 identity = glm::mat4(1.0);

    GLint viewMatLocation = glGetUniformLocation(m_hdr_shader, "viewMat1");
    glUniformMatrix4fv(viewMatLocation, 1, GL_FALSE, &identity[0][0]); //passing in the right matrix messes stuff up

    GLint projMatLocation = glGetUniformLocation(m_hdr_shader, "projMat1");
    glUniformMatrix4fv(projMatLocation, 1, GL_FALSE, &m_projTest[0][0]); //passing in the right matrix messes stuff up

    GLint boolLoc = glGetUniformLocation(m_hdr_shader, "deadParticle");
    glUniform1i(boolLoc, isDissolved);


    if(isDissolved){
        isDissolved = false;
    }
    GLint incLoc = glGetUniformLocation(m_hdr_shader, "incrementer");
    glUniform1f(incLoc , currPart.particleIncrementor);

    //    //if(isDissolved){
    //    std::cout << "Updated Offset" << currPart.offset[1]<< std::endl;
    //    //}
    GLint offsetLocation = glGetUniformLocation(m_hdr_shader, "offer");
    glUniform3fv(offsetLocation, 1, &currPart.offset[0]);



    //if(currPart.lifetime > 0){
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);

    //    else{
    //    currPart.offset[1] = 0.5f;
    //    currPart.lifetime = 200/pow(offset[2],2);
    //    glDrawArrays(GL_TRIANGLES, 0, 6);
    //    glBindTexture(GL_TEXTURE_2D, 0);
    //    glBindVertexArray(0);
    //    glUseProgram(0);
    //    }
    // }


}

void Realtime::resizeGL(int w, int h) {
    // Tells OpenGL how big the screen is
    glViewport(0, 0, size().width() * m_devicePixelRatio, size().height() * m_devicePixelRatio);

    //    glDeleteTextures(1, &m_new_fbo_texture);
    //    glDeleteRenderbuffers(1, &m_new_fbo_renderbuffer);
    //    glDeleteFramebuffers(1, &m_n)

    projWidth = w;
    projHeight = h;
    // Students: anything requiring OpenGL calls when the program starts should be done here
    //Maybe stuff with camera?
}

void Realtime::sceneChanged() {

    //makeCurrent();


    //Populates meta data with the scene information
    SceneParser::parse(settings.sceneFilePath, metaData);

    camera = Cam(metaData.cameraData, projWidth, projHeight, settings.nearPlane, settings.farPlane);
    m_view = camera.getViewMatrix();
    m_proj = camera.getProjectMatrix();

    std::cout<< "meta call" << std::endl;
    std::cout<< metaData.shapes[0].ctm[0][2] << std::endl;
    std::cout<< "meta call" << std::endl;

    GenerateCity();

    update(); // asks for a PaintGL() call to occur



}

void Realtime::settingsChanged() {
    //make it better with settingsPrevious
    if(settingsCalled){
        camera.updateCamFarPlane(settings.farPlane);
        camera.updateCamNearPlane(settings.nearPlane);

        tempCube.updateParams(settings.shapeParameter1);

        tempSphere.updateParams(settings.shapeParameter1, settings.shapeParameter2);
        templateSphereData = tempSphere.generateShape();
        binderHelper(m_sphere_vao, m_sphere_vbo, templateSphereData);

        tempCylinder.updateParams(settings.shapeParameter1, settings.shapeParameter2);
        templateCylinderData = tempCylinder.generateShape();
        binderHelper(m_cylinder_vao, m_cylinder_vbo, templateCylinderData);

        tempCone.updateParams(settings.shapeParameter1);
        templateConeData = tempCone.generateShape(true);
        binderHelper(m_cone_vao, m_cone_vbo, templateConeData);









        //    Figure out how to update vbo's to account for more tesselations.
        //    sphere.updateParams()
        //    sphere.generate shape
        //     update vbos



        GenerateCity();
        update(); // asks for a PaintGL() call to occur
    }
}

// ================== Project 6: Action!"W pressed"



void Realtime::keyPressEvent(QKeyEvent *event) {
    m_keyMap[Qt::Key(event->key())] = true;


}

void Realtime::keyReleaseEvent(QKeyEvent *event) {
    m_keyMap[Qt::Key(event->key())] = false;
}

void Realtime::mousePressEvent(QMouseEvent *event) {
    if (event->buttons().testFlag(Qt::LeftButton)) {
        m_mouseDown = true;
        m_prev_mouse_pos = glm::vec2(event->position().x(), event->position().y());
    }
}

void Realtime::mouseReleaseEvent(QMouseEvent *event) {
    if (!event->buttons().testFlag(Qt::LeftButton)) {
        m_mouseDown = false;
    }
}

glm::mat4 rotHelper(float t, glm::vec3 u){

    float a21 = (u[0] * u[1] * (1 - cos(t))) + (u[2] * sin(t));
    float a12 = (u[0] * u[1] * (1 - cos(t))) - (u[2] * sin(t));

    float a31 = (u[0] * u[2] * (1 - cos(t))) - (u[1] * sin(t));
    float a13 = (u[0] * u[2] * (1 - cos(t))) + (u[1] * sin(t));

    float a32 = (u[1] * u[2] * (1 - cos(t))) + (u[0] * sin(t));
    float a23 = (u[1] * u[2] * (1 - cos(t))) - (u[0] * sin(t));

    glm::vec4 tcol0(cos(t) + (pow(u[0],2) * (1.f - cos(t)) ), a21, a31, 0);
    glm::vec4 tcol1(a12, cos(t) + (pow(u[1],2) * (1.f - cos(t)) ), a32, 0);
    glm::vec4 tcol2(a13, a23, cos(t) + (pow(u[2],2) * (1.f - cos(t)) ), 0);
    glm::vec4 tcol3(0,0,0,1);

    glm::mat4 rot(tcol0, tcol1, tcol2, tcol3);
    return rot;

}

void Realtime::mouseMoveEvent(QMouseEvent *event) {
    if (m_mouseDown) {
        int posX = event->position().x();
        int posY = event->position().y();
        int deltaX = posX - m_prev_mouse_pos.x;
        int deltaY = posY - m_prev_mouse_pos.y;
        m_prev_mouse_pos = glm::vec2(posX, posY);

        // Use deltaX and deltaY here to rotate

        float thetaX = deltaX * 0.005;
        glm::vec3 xRotAxis(0.f, 1.f, 0.f);

        float thetaY = deltaY * 0.005;
        glm::vec3 yRotAxis = glm::vec3(glm::normalize(glm::cross(glm::vec3(camera.look), glm::vec3(camera.up))));

        camera.look = rotHelper(thetaY, yRotAxis) * rotHelper(thetaX, xRotAxis) * camera.look;
        camera.updateViewMatrix(camera.pos,camera.look,camera.up); /*m_view * translate * glm::mat4(5.f * deltaTime * lookDir, 5.f * deltaTime * lookDir, 5.f * deltaTime * lookDir, 5.f * deltaTime * lookDir);*/
        m_view = camera.getViewMatrix();

        update(); // asks for a PaintGL() call to occur
    }
}

void Realtime::timerEvent(QTimerEvent *event) {
    int elapsedms   = m_elapsedTimer.elapsed();
    float deltaTime = elapsedms * 0.001f;
    m_elapsedTimer.restart();

    // Use deltaTime and m_keyMap here to move around
    glm::vec4 lookDir = glm::normalize(camera.look);
    glm::vec4 worldUp = glm::vec4(0.f, 1.f, 0.f, 1.f);
    glm::vec4 right = glm::vec4(glm::normalize(glm::cross(glm::vec3(camera.look), glm::vec3(camera.up))), 1.f);
    glm::mat4 translate(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 5 * deltaTime * lookDir[0], 5 * deltaTime * lookDir[1], 5 * deltaTime * lookDir[2], 1);

    for(int i = 0; i < particles.size(); i++){
        particles[i].particleIncrementor += sqrt(particles[i].offset[2]) * 0.5f;
        particles[i].lifetime -= 1;
        if(particles[i].lifetime < 0){
            particles[i].isAlive = false;
        }

        //std::cout << particles[i].isAlive << std::endl;
    }
    //std::cout << m_keyMap[Qt::Key_W] << std::endl;
    if(m_keyMap[Qt::Key_W]){

        camera.pos += 5.f * deltaTime * lookDir;
        camera.updateViewMatrix(camera.pos, camera.look,camera.up); /*m_view * translate * glm::mat4(5.f * deltaTime * lookDir, 5.f * deltaTime * lookDir, 5.f * deltaTime * lookDir, 5.f * deltaTime * lookDir);*/
        m_view = camera.getViewMatrix();

        for(int i = 0; i < particles.size(); i++){
            particles[i].particleIncrementor += sqrt(particles[i].offset[2]) * 0.5f;
            particles[i].lifetime -= 1;
            if(particles[i].lifetime < 0){
                particles[i].isAlive = false;
            }

            //std::cout << particles[i].isAlive << std::endl;
        }



    }

    if(m_keyMap[Qt::Key_S]){
        //std::cout << "S pressed" << std::endl;
        camera.pos -= 1.f * deltaTime * lookDir;
        camera.updateViewMatrix(camera.pos, camera.look,camera.up); /*m_view * translate * glm::mat4(5.f * deltaTime * lookDir, 5.f * deltaTime * lookDir, 5.f * deltaTime * lookDir, 5.f * deltaTime * lookDir);*/
        m_view = camera.getViewMatrix();
        incrementer -= 0.5f;

        particleRemover();


    }

    if(m_keyMap[Qt::Key_A]){
        // std::cout << "A pressed" << std::endl;
        camera.pos -= 5.f * deltaTime * right;
        camera.updateViewMatrix(camera.pos, camera.look,camera.up); /*m_view * translate * glm::mat4(5.f * deltaTime * lookDir, 5.f * deltaTime * lookDir, 5.f * deltaTime * lookDir, 5.f * deltaTime * lookDir);*/
        m_view = camera.getViewMatrix();

    }

    if(m_keyMap[Qt::Key_D]){
        // std::cout << "D pressed" << std::endl;

        camera.pos += 5.f * deltaTime * right;
        camera.updateViewMatrix(camera.pos, camera.look,camera.up); /*m_view * translate * glm::mat4(5.f * deltaTime * lookDir, 5.f * deltaTime * lookDir, 5.f * deltaTime * lookDir, 5.f * deltaTime * lookDir);*/
        m_view = camera.getViewMatrix();

    }

    if(m_keyMap[Qt::Key_Space]){
        // std::cout << "space pressed" << std::endl;
        camera.pos += 5.f * deltaTime * worldUp;
        camera.updateViewMatrix(camera.pos, camera.look,camera.up); /*m_view * translate * glm::mat4(5.f * deltaTime * lookDir, 5.f * deltaTime * lookDir, 5.f * deltaTime * lookDir, 5.f * deltaTime * lookDir);*/
        m_view = camera.getViewMatrix();

    }

    if(m_keyMap[Qt::Key_Control]){
        // std::cout << "ctrl pressed" << std::endl;
        camera.pos -= 5.f * deltaTime * worldUp;
        camera.updateViewMatrix(camera.pos, camera.look,camera.up); /*m_view * translate * glm::mat4(5.f * deltaTime * lookDir, 5.f * deltaTime * lookDir, 5.f * deltaTime * lookDir, 5.f * deltaTime * lookDir);*/
        m_view = camera.getViewMatrix();

    }

    update(); // asks for a PaintGL() call to occur
}


// DO NOT EDIT
void Realtime::saveViewportImage(std::string filePath) {
    // Make sure we have the right context and everything has been drawn
    makeCurrent();

    int fixedWidth = 1024;
    int fixedHeight = 768;

    // Create Frame Buffer
    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    // Create a color attachment texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, fixedWidth, fixedHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    // Optional: Create a depth buffer if your rendering uses depth testing
    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, fixedWidth, fixedHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Error: Framebuffer is not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return;
    }

    // Render to the FBO
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glViewport(0, 0, fixedWidth, fixedHeight);

    // Clear and render your scene here
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    paintGL();

    // Read pixels from framebuffer
    std::vector<unsigned char> pixels(fixedWidth * fixedHeight * 3);
    glReadPixels(0, 0, fixedWidth, fixedHeight, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

    // Unbind the framebuffer to return to default rendering to the screen
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Convert to QImage
    QImage image(pixels.data(), fixedWidth, fixedHeight, QImage::Format_RGB888);
    QImage flippedImage = image.mirrored(); // Flip the image vertically

    // Save to file using Qt
    QString qFilePath = QString::fromStdString(filePath);
    if (!flippedImage.save(qFilePath)) {
        std::cerr << "Failed to save image to " << filePath << std::endl;
    }

    // Clean up
    glDeleteTextures(1, &texture);
    glDeleteRenderbuffers(1, &rbo);
    glDeleteFramebuffers(1, &fbo);
}
