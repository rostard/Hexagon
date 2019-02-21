//
// Created by rostard on 25.09.18.
//

#include "Shader.h"
#include "common.h"

Shader* Shader::defaultSpriteShader = nullptr;
Shader* Shader::defaultFontShader = nullptr;
Shader* Shader::defaultPickShader = nullptr;

Shader::Shader(const std::string &vertexSource, const std::string &fragmentSource, const std::string &geometrySource) {
    id = createShader(vertexSource, fragmentSource, geometrySource);
}

void Shader::use() {
    glUseProgram(id);
}

unsigned int Shader::createShader(const std::string &vertexSource, const std::string &fragmentSource,
                                  const std::string &geometrySource) {
    unsigned int vShader = compileShader(vertexSource, GL_VERTEX_SHADER);
    unsigned int fShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);
    unsigned int gShader = 0;
    if(!geometrySource.empty()){
        gShader = compileShader(geometrySource, GL_GEOMETRY_SHADER);
    }


    unsigned int program = glCreateProgram();
    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    if(!geometrySource.empty()){
        glAttachShader(program, gShader);
    }

    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success){
        char buf[512];
        glGetProgramInfoLog(program, 512, nullptr, buf);
        std::cerr<<"Program: "<<buf<<std::endl;
    }
    glDeleteShader(vShader);
    glDeleteShader(fShader);
    if(!geometrySource.empty()){
        glDeleteShader(gShader);
    }
    return program;
}

unsigned int Shader::compileShader(const std::string &source, GLenum type) {
    unsigned int shader = glCreateShader(type);
    const char* csource = source.c_str();
    glShaderSource(shader, 1, &csource, nullptr);
    glCompileShader(shader);

    int success;
    char buf[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(shader, 512, nullptr, buf);
        std::string shaderType = shaderTypeToStr(type);
        std::cerr<<shaderType<<": "<<buf<<std::endl;
    }
    return shader;
}

void Shader::setUniform1i(const std::string &name, int i) {
    glUniform1i(glGetUniformLocation(id, name.c_str()), i);
}

void Shader::setUniform2f(const std::string &name, float f1, float f2) {
    glUniform2f(glGetUniformLocation(id, name.c_str()), f1, f2);
}

void Shader::setUniform2f(const std::string &name, vec2 vec) {
    setUniform2f(name, vec.x, vec.y);
}

void Shader::setUniformMat2(const std::string &name, const mat2& mat) {
    glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, (float*)&mat);
}

void Shader::setWindowSize(unsigned int window_width, unsigned int window_height) {
    use();
    setUniform2f("windowSize", window_width, window_height);
}

Shader *Shader::GetSpriteShader() {
    if (Shader::defaultSpriteShader == nullptr){
        auto vertex = readFile("res/shaders/sprite_shader.vs.glsl");
        auto fragment= readFile("res/shaders/sprite_shader.fs.glsl");
        Shader::defaultSpriteShader = new Shader(vertex, fragment);
    }
    return Shader::defaultSpriteShader;
}

Shader *Shader::GetPickShader() {
    if (Shader::defaultPickShader == nullptr){
        auto vertex = readFile("res/shaders/pick_shader.vs.glsl");
        auto fragment= readFile("res/shaders/pick_shader.fs.glsl");
        Shader::defaultPickShader = new Shader(vertex, fragment);
    }
    return Shader::defaultPickShader;
}

void Shader::setUniform3f(const std::string &name, float f1, float f2, float f3) {
    glUniform3f(glGetUniformLocation(id, name.c_str()), f1, f2, f3);
}

void Shader::setUniform3f(const std::string &name, vec3 vec) {
    setUniform3f(name, vec.x, vec.y, vec.z);
}

Shader *Shader::GetFontShader() {
    if (Shader::defaultFontShader == nullptr){
        auto vertex = readFile("res/shaders/font_shader.vs.glsl");
        auto fragment= readFile("res/shaders/font_shader.fs.glsl");
        Shader::defaultFontShader = new Shader(vertex, fragment);
    }
    return defaultFontShader;
}


std::string shaderTypeToStr(GLenum type) {
    if (type ==GL_VERTEX_SHADER)
        return "Vertex Shader";
    else if (type ==GL_FRAGMENT_SHADER)
        return "Fragment Shader";
    else if (type ==GL_GEOMETRY_SHADER)
        return "Geometry Shader";
    return "Non Shader";
}