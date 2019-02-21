#version 330

layout (location=0) in vec2 inPos;
layout (location=1) in vec2 inTex;
uniform vec2 windowSize;

uniform vec2 pos;
uniform vec2 scale;
uniform mat2 rot;

out vec2 TexCoords;

void main() {
    TexCoords = inTex;
    vec2 pos = ((rot*(scale * inPos.xy)) + vec2(pos.x, -pos.y) + vec2(scale.x, -scale.y));
    gl_Position = vec4(pos / windowSize - vec2(1, -1), 0.0, 1.0);
}
