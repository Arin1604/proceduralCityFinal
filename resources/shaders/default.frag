#version 330 core

//Testing with primitive lab09 version
in vec3 worldSpacePos;
in vec3 worldSpaceNorm;

out vec4 fragColor;

float fallOffHelper(vec3 lightDir, vec3 dirFromLight, float angle, float penumbra);

//make struct
struct SceneLights{
int type;

vec3 color;
vec3 attenuation; // Attenuation function

vec3 pos; // Position with CTM applied (Not applicable to directional lights)
vec3 dir; // Direction with CTM applied (Not applicable to point lights)

float penumbra; // Only applicable to spot lights, in RADIANS
float angle;    // Only applicable to spot lights, in RADIANS


};



//

//pass in array of light structs

//Light data
uniform SceneLights lights[145];
uniform vec3 lightColors[100];



//Updated for all lights now
uniform int arraySize;


//Scene vals
uniform float k_A;
uniform float k_D;
uniform float k_S;
uniform vec4 cameraPos;
uniform float shine;

//object colors
uniform vec3 m_A;
uniform vec3 m_S;
uniform vec3 m_D;

void main() {
    fragColor = vec4(1.0);
    float RedAcc;
    float GreenAcc;
    float BlueAcc;

    vec3 cameraDir = normalize(vec3(cameraPos) - worldSpacePos);//double check
    vec3 normal = normalize(worldSpaceNorm);

    RedAcc = k_A * m_A[0];
    GreenAcc = k_A * m_A[1];
    BlueAcc = k_A * m_A[2];

    vec3 dirLight;
    float att;
    float fallOff = 1.f;

    //Diffuse term
   for(int i = 0; i < arraySize; i++){

       if(lights[i].type == 0){
           dirLight = -normalize(vec3(lights[i].dir[0], lights[i].dir[1], lights[i].dir[2] ));
           att = 1.f;
       }

       else{
           dirLight = vec3(lights[i].pos[0], lights[i].pos[1], lights[i].pos[2]) - vec3(worldSpacePos[0], worldSpacePos[1], worldSpacePos[2]);

           float d = length(dirLight);

           att = 1.f / (lights[i].attenuation[0] + lights[i].attenuation[1] * d + lights[i].attenuation[2] * pow(d,2));

           dirLight = normalize(dirLight);




           if(lights[i].type == 2){
               fallOff = fallOffHelper(lights[i].dir, -dirLight, lights[i].angle, lights[i].penumbra);
           }

       }

       float product = dot(normalize(normal), normalize(dirLight));
       if (product < 0) product = 0.0;
       if (product > 1) product = 1.0;

       RedAcc += fallOff * att * k_D * m_D[0] * product * lights[i].color[0];
       GreenAcc +=  fallOff * att * k_D * m_D[1] * product * lights[i].color[1];
       BlueAcc += fallOff * att * k_D * m_D[2] * product * lights[i].color[2];




       //Specular Terms
    vec3 reflected = normalize(reflect(-dirLight, normal));
    float dotP = dot(normalize(cameraDir), normalize(reflected));
    if (dotP < 0) dotP = 0.0;
    if (dotP > 1) dotP = 1.0;

    float power;
    if (shine > 0 && dotP > 0){
        power = pow(dotP, shine);
    } else{
       power = 0;
    }

    if(shine > 0 && dotP > 0){
        RedAcc += fallOff * att * k_S * m_S[0] * power * lights[i].color[0];
        GreenAcc +=  fallOff * att * k_S * m_S[1] * power * lights[i].color[1];
        BlueAcc += fallOff * att * k_S * m_S[2] * power * lights[i].color[2];


    }



}


   fragColor[0] = RedAcc;
   fragColor[1] = GreenAcc;
   fragColor[2] = BlueAcc;


}

float fallOffHelper(vec3 lightDir, vec3 dirFromLight, float angle, float penumbra){
    float cos = dot(lightDir, dirFromLight) / (length(lightDir) * length(dirFromLight));
    float x = acos(cos);
    float inner = angle - penumbra;
    float outer = angle;
    if(x < inner){
        return 1.f;
    }
    else if(x < outer){
        float t1 = -2.f * pow((x - inner) / (outer - inner), 3);
        float t2 = 3.f * pow((x - inner) / (outer - inner), 2);
        return 1.f - (t1 + t2);
    }
    else{
        return 0.f;
    }
}


