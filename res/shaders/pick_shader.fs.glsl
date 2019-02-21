#version 330

uniform int index;

uniform sampler2D texture0;
in vec2 TexCoords;
void main() {
    if(texture(texture0, TexCoords).a == 0) discard;
    int r = index % 255;
    int g = (index / 255) % 255;
    int b = (index / 255 / 255) % 255;
    gl_FragColor = vec4(r/255., g/255., b/255., 1.0);

}
