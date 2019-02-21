#version 330 core

layout (location = 0)in vec2 inPos;
layout (location = 1)in vec2 inTex;

uniform vec2 pos;
uniform vec2 scale;
uniform vec2 offset;

uniform vec2 windowSize;

out vec2 TexCoords;

void main() {
    TexCoords = inTex;
    gl_Position = vec4((inPos*scale + pos + vec2(offset.x, -offset.y)) / windowSize - vec2(1, -1), 1.0, 1.0);
}
