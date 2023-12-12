#version 330 core

in vec2 uvCoord;


uniform sampler2D text;
uniform int inverter;

uniform int screenW;
uniform int screenH;

out vec4 fragColor;

void main()
{
    fragColor = vec4(1);
    // Task 17: Set fragColor using the sampler2D at the UV coordinate
    fragColor = texture(text, uvCoord);

    if(inverter == 2){

        //    float u = (uvCoord[0]);
        //    float v = (uvCoord[1]);

        //    int uPrime = int(screenW * u);
        //    int vPrime = int(screenH * v);

        //    vec4 acc = vec4(0);


        for(int i = -2; i <= 2; i++){
            for(int j = -2; j <= 2; j++){
                //            int currX = uPrime + i;
                //            int currY = uPrime + j;
                //            float currXUV = float(currX/screenW);
                //            float currYUV = float(currY/screenH);

                //            vec2 newUV = vec2(currXUV, currYUV);
                float scale = 1/ sqrt((screenH * screenW));
                vec2 offset = vec2(i,j) * scale;

                fragColor += texture(text, uvCoord + offset);
            }
        }

        fragColor /= 25.0;
    }

    if(inverter == 1){
        float exposure = 5.f;
        const float gamma = 2.2f;
        vec3 hdr = texture(text, uvCoord).rgb;

        vec3 mapped = vec3(1.f) - exp(-hdr * exposure);
        // gamma correction
        mapped = pow(mapped, vec3(1.f / gamma));
        fragColor = vec4(mapped, 1.f);

        for(int i = -2; i <= 2; i++){
            for(int j = -2; j <= 2; j++){
                //            int currX = uPrime + i;
                //            int currY = uPrime + j;
                //            float currXUV = float(currX/screenW);
                //            float currYUV = float(currY/screenH);

                //            vec2 newUV = vec2(currXUV, currYUV);
                float scale = 1/ sqrt((screenH * screenW));
                vec2 offset = vec2(i,j) * 0.003;

                fragColor += texture(text, uvCoord + offset);
            }
        }

        fragColor /= 25.f;


    }



    //if (inverter){
    //        fragColor[0] = 1.f - fragColor[0];
    //        fragColor[1] = 1.f - fragColor[1];
    //        fragColor[2] = 1.f - fragColor[2];
    //   fragColor = acc;
    // }

    //        fragColor[0] = (screenH/2)/454.f;
    //        fragColor[1] = (screenH/2)/454.f;
    //        fragColor[2] = (screenW/2)/606.f;

//    fragColor = vec4(1.0);



}
