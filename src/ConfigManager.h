//
// Created by rostard on 26.09.18.
//

#ifndef INC_2DPROJECT_CONFIGMANAGER_H
#define INC_2DPROJECT_CONFIGMANAGER_H


#include <string>
#include <map>
#include "math.h"

class ConfigManager {
public:
    ConfigManager() = delete;
    static void LoadConfig(const std::string& fileName);
    static float getFloat(const std::string& name);
    static std::string getString(const std::string& name);
    static vec2 getVec2(const std::string& name);
    static vec3 getVec3(const std::string& name);

private:
    static std::map<std::string, std::string> stringValues;
    static std::map<std::string, float> floatValues;
    static std::map<std::string, vec2> vec2Values;
    static std::map<std::string, vec3> vec3Values;
};


#endif //INC_2DPROJECT_CONFIGMANAGER_H
