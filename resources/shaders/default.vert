#version 330 core

layout(location = 0) in vec3 objSpacePos;
layout(location = 1) in vec3 objSpaceNorm;

// Task 5: declare `out` variables for the world-space position and normal,
//         to be passed to the fragment shader
out vec3 worldSpacePos;
out vec3 worldSpaceNorm;

// Task 6: declare a uniform mat4 to store model matrix
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

// Task 7: declare uniform mat4's for the view and projection matrix

void main() {
    // Task 8: compute the world-space position and normal, then pass them to
    //         the fragment shader using the variables created in task 5
    //worldSpacePos = vec3(modelMat * vec4(objSpacePos, 1.0));// Kind of shady stuff goin on here no?
    mat3 model = mat3(modelMat);
    worldSpacePos = model * objSpacePos;
    worldSpaceNorm = inverse(transpose(model)) * objSpaceNorm;


    // Recall that transforming normals requires obtaining the inverse-transpose of the model matrix!
    // In projects 5 and 6, consider the performance implications of performing this here.
    // Task 9: set gl_Position to the object space position transformed to clip space
    gl_Position = projMat * viewMat * modelMat * vec4(objSpacePos, 1.0);
}
