//
// Created by rostard on 26.09.18.
//

#include "ConfigManager.h"
#include "common.h"
#include <algorithm>
std::map<std::string, std::string> ConfigManager::stringValues;
std::map<std::string, float> ConfigManager::floatValues;
std::map<std::string, vec2> ConfigManager::vec2Values;
std::map<std::string, vec3> ConfigManager::vec3Values;

void ConfigManager::LoadConfig(const std::string &fileName) {
    std::ifstream file(fileName);
    std::string string;

    while(!file.eof()){
        std::getline(file, string);

        int delPos = string.find(' ');
        std::string key = string.substr(0,delPos);
        std::string val = string.substr(delPos+1);

        if(val[0]=='"'){ //String
            stringValues[key] = val.substr(1, val.size()-2);
        }
        else if(val[0]=='('){ //Vector
            float components[3]; //Vector components
            unsigned long last_pos = 1;

            for(int i = 0; i < 3; i++){
                unsigned long pos = val.find(' ', last_pos);

                if(pos == std::string::npos){ //Last component
                    components[i] = std::stof(val.substr(last_pos, val.size()-2));
                    if(i == 1){ // vec2
                        vec2Values[key] = {components[0], components[1]};
                    }
                    else if(i == 2){ // vec3
                        vec3Values[key] = {components[0], components[1], components[2]};
                    }
                    break;
                }
                components[i] = std::stof(val.substr(last_pos, pos));
                last_pos = pos+1;
            }
        }
        else{ //float
            floatValues[key] = std::stof(val);
        }
//        std::cerr<<key<<":"<<val<<std::endl;
    }
}

float ConfigManager::getFloat(const std::string &name) {
    return floatValues[name];
}

std::string ConfigManager::getString(const std::string &name) {
    return stringValues[name];
}

vec2 ConfigManager::getVec2(const std::string &name) {
    return vec2Values[name];
}

vec3 ConfigManager::getVec3(const std::string &name) {
    return vec3Values[name];
}