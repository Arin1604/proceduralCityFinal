#version 330 core

//IS SNOW FINAL
in vec2 uvCoord;
in vec3 loc;


uniform sampler2D hdr_texture;


out vec4 fragColor;

void main()
{
//    fragColor = texture(hdr_texture, uvCoord);

//    if(fragColor[0] + 0.5 > 1.0){
//       fragColor[0] = 1.0;
//    }

//    else{
//        fragColor[0] += 0.5;
//    }


    fragColor = vec4(1.0);
    if(loc[1] < -0.7){
      fragColor = vec4(0.5);
    }


}
