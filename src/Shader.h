//
// Created by rostard on 25.09.18.
//

#ifndef INC_2DPROJECT_SHADER_H
#define INC_2DPROJECT_SHADER_H


#include <glad/glad.h>
#include <string>
#include <iostream>
#include "math.h"

std::string shaderTypeToStr(GLenum type);

class Shader {
public:
    Shader(const std::string& vertexSource, const std::string& fragmentSource, const std::string& geometrySource = "");
    void use();
    void setUniform1i(const std::string &name, int f);
    void setUniform2f(const std::string& name, float f1, float f2);
    void setUniform2f(const std::string& name, vec2 vec);
    void setUniform3f(const std::string& name, float f1, float f2, float f3);
    void setUniform3f(const std::string& name, vec3 vec);
    void setUniformMat2(const std::string& name, const mat2& mat);
    void setWindowSize(unsigned int window_width, unsigned int window_height);
    static Shader* GetSpriteShader();
    static Shader* GetFontShader();
    static Shader* GetPickShader();
private:
    unsigned int compileShader(const std::string& source, GLenum type);
    unsigned int createShader(const std::string& vertexSource, const std::string& fragmentSource, const std::string& geometrySource = "");

    unsigned int id;

    static Shader* defaultSpriteShader;
    static Shader* defaultFontShader;
    static Shader* defaultPickShader;

};


#endif //INC_2DPROJECT_SHADER_H
