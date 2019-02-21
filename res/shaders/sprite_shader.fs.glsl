#version 330


uniform vec3 color;
uniform sampler2D texture0;

in vec2 TexCoords;

void main() {
    vec4 texColor = texture(texture0, TexCoords);
    gl_FragColor = vec4(color*texColor.xyz, texColor.w);
}
