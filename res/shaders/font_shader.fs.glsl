#version 330 core

in vec2 TexCoords;

uniform sampler2D texture0;
uniform vec3 color;
void main() {
    float op = texture(texture0, TexCoords).r;
    gl_FragColor = vec4(color, 1.0) * vec4(1.0, 1.0, 1.0, op);
}
