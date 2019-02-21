//
// Created by rostard on 26.09.18.
//

#include "common.h"

std::string readFile(const std::string &filename) {
    std::ifstream file(filename);
    std::string content( (std::istreambuf_iterator<char>(file)),
                         (std::istreambuf_iterator<char>()    ) );
    return content;

}
