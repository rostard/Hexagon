//
// Created by rostard on 10.02.19.
//

#ifndef INC_2DPROJECT_FRAMEBUFFER_H
#define INC_2DPROJECT_FRAMEBUFFER_H


class Framebuffer {
public:
    Framebuffer(unsigned int width, unsigned int height);

    virtual ~Framebuffer();

    void bind();
    void clear();
private:
    GLuint id;
};


#endif //INC_2DPROJECT_FRAMEBUFFER_H
