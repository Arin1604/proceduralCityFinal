#version 330 core

//IS SNOW FINAL
// Task 15: add a second layout variable representing a UV coordinate
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureName;

// Task 16: create an "out" variable representing a UV coordinate
out vec2 uvCoord;
out vec3 loc;

uniform mat4 viewMat1;
uniform mat4 projMat1;
uniform float incrementer;

uniform int deadParticle;


uniform vec3 offer;

void main() {
    // Task 16: assign the UV layout variable to the UV "out" variable

    vec4 pos = vec4(position, 1.0);


    pos.x = pow(offer[2],3) * 2.f * position.x;//add params
    pos.y = pow(offer[2], 3) * 2.f * position.y;//add params

    pos.x += 1 * (position.x - (offer[0])); //the 0 here is the offset we get from particle
    pos.y += 1 * (position.y - (offer[1])); //the 0 here is the offset we get from particle

    pos.y += 0.01 * (position.y - (incrementer));

//    if(pos.y > 0.6){
//        pos.y += 0.01 * (position.y + ( 2 * incrementer));

//    }
//    if(pos.y < -0.4){
//        pos.y += 0.01 * (position.y + ( 0.8 * incrementer));

//    }


if(deadParticle == 1){
    pos.y = 0;
}

    gl_Position =pos;

    uvCoord = textureName;
    loc = vec3(pos);
}
