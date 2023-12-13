#version 330 core

in vec2 uvCoord;


uniform sampler2D texte;
uniform sampler2D blur;




out vec4 fragColor;

void main()
{
    vec4 a = texture(texte, uvCoord);
    vec4 b = texture(blur, uvCoord);

    fragColor = a + b;


}








