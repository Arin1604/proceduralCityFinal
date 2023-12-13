#pragma once

//IS SNOW FINAL
// Defined before including GLEW to suppress deprecation messages on macOS
#include "cam.h"
#include "cone.h"
#include "cube.h"
#include "cylinder.h"
#include "snow.h"
#include "sphere.h"
#include "utils/sceneparser.h"
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <unordered_map>
#include <QElapsedTimer>
#include <QOpenGLWidget>
#include <QTime>
#include <QTimer>
#include "Building.h"
class Realtime : public QOpenGLWidget
{
public:
    Realtime(QWidget *parent = nullptr);
    void finish();                                      // Called on program exit
    void sceneChanged();
    void settingsChanged();
    void saveViewportImage(std::string filePath);
    void getData();
    void binderHelper(GLuint VAO, GLuint VBO, std::vector<float> vertexData/* PrimitiveType shapeType*/);
    void generateData();
    void lightsHelper(std::vector<SceneLightData> lights, GLuint shader);
    void lightsColorHelper(std::vector<SceneLightData> lights, GLuint shader);
    int getNumberOfLights(std::vector<SceneLightData> lights);
    // helper functions for final project:
    void GenerateCity();
    float getRandomFloat(float min, float max);
    std::vector<float> generateRandomCubes();
public slots:
    void tick(QTimerEvent* event);                      // Called once per tick of m_timer

protected:
    void initializeGL() override;                       // Called once at the start of the program
    void paintGL() override;                            // Called whenever the OpenGL context changes or by an update() request
    void resizeGL(int width, int height) override;      // Called when window size changes

private:
    struct Particle
    {
        glm::vec3 offset;
        int index;
        //        offset[2] = 0.9f
        int lifetime = 200/pow(offset[2],2);
        float particleIncrementor = offset[2];
        bool isAlive = true;

        bool operator() (Particle i, Particle j) {return (i.isAlive > j.isAlive);}
    } particle;

    std::vector< Particle > particles;

    int numberOfParticles = 200;

    bool settingsCalled = false;
    GLuint m_texture_shader; //stores id of textue
    GLuint m_shader; // Stores id of shader program
    GLuint m_hdr_shader;
    GLuint m_vbo;    // Stores id of VBO
    GLuint m_vao;    // Stores id of
    float incrementer = 0.f;
    int lifeSpan = 100;

    GLuint m_new_fbo;
    GLuint m_new_fbo_texture;
    GLuint m_new_fbo_renderbuffer;

    GLuint m_hdr_fbo;
    GLuint m_hdr_fbo_texture;
    GLuint m_hdr_fbo_renderbuffer;

    GLuint m_blur_texture;
    GLuint m_bloom_texture;

    QImage m_image;
    GLuint m_kitten_texture;

    GLuint m_fullscreen_vbo;
    GLuint m_fullscreen_vao;

    GLuint m_sphere_vbo;    // Stores id of VBO
    GLuint m_sphere_vao;    // Stores id of VAO

    GLuint m_cylinder_vao;    // Stores id of VAO
    GLuint m_cylinder_vbo;

    GLuint m_cube_vbo;    // Stores id of VBO
    GLuint m_cube_vao;    // Stores id of VAO

    GLuint m_cone_vbo;    // Stores id of VBO
    GLuint m_cone_vao;

    GLuint m_snow_vbo;    // Stores id of VBO
    GLuint m_snow_vao;

    std::vector<float> templateSphereData;
    std::vector<float> templateCubeData;
    std::vector<float> templateCylinderData;
    std::vector<float> templateConeData;

    std::vector<float> m_snowData;

    Cam camera;
    glm::mat4 m_modelTest = glm::mat4(1);
    glm::mat4 m_viewTest = glm::mat4(1);
    glm::mat4 m_projTest = glm::mat4(1);
    glm::mat4 m_view;
    glm::mat4 m_proj;

    GLuint m_defaultFBO;

    sphere tempSphere;
    cube tempCube;
    cylinder tempCylinder;
    cone tempCone;
    snow tempSnow;

    int m_screen_width;
    int m_screen_height;
    int m_fbo_width;
    int m_fbo_height;

    int projWidth;
    int projHeight;
    void paintTexture(GLuint texture, int process);
    void paintSnow(GLuint shader, glm::mat4 view, glm::mat4 proj, glm::vec3 offset, Particle currPart);
    void makeFBO();
    void makeHdrFBO();
    void snowBinder();
    void particleRemover();
    void addParticle(float x, float y, float z, int i);
    void removeParticle(int i);
    void insertVec3(std::vector<float> &data, glm::vec3 v);
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

    // Tick Related Variables
    int m_timer;                                        // Stores timer which attempts to run ~60 times per second
    QElapsedTimer m_elapsedTimer;                       // Stores timer which keeps track of actual time between frames

    // Input Related Variables
    bool m_mouseDown = false;                           // Stores state of left mouse button
    glm::vec2 m_prev_mouse_pos;                         // Stores mouse position
    std::unordered_map<Qt::Key, bool> m_keyMap;         // Stores whether keys are pressed or not

    // Device Correction Variables
    int m_devicePixelRatio;

    RenderData metaData;

    // below are fields for final project:
    std::vector<glm::mat4> m_CTM_collection; // stores different CTMs for the cubes
    std::vector<Building> m_building_arr; // stores the buildings

};
