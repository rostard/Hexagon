#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>

#include "common.h"
#include "Shader.h"
#include "Texture.h"
#include "Sprite.h"
#include "ConfigManager.h"
#include "gui/GUIButton.h"
#include "gui/Font.h"
#include "gui/GUILabel.h"
#include "Framebuffer.h"
#include "HexField.h"

int keys[512];
int keysDown[512];

bool frameMode = false;

void on_hover(ClickableSprite* sprite){
    sprite->setColor({0.5f, 0.5f, 0.5f});
}
void on_hover_off(ClickableSprite* sprite){
    sprite->setColor({1.0, 1.0, 1.0});
}

void run_away(ClickableSprite* sprite){
    vec2 offset = {1, 0};
    sprite->setPos(offset + sprite->getPos());
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS){

        keysDown[key] = !keys[key];
        keys[key] = true;
    }
    else if(action == GLFW_RELEASE){
        keys[key] = false;
        keysDown[key] = false;
    }
    else if(action == GLFW_REPEAT){
        keysDown[key] = false;
    }
}

//returns 0 if ther's none sprites
int getIndex(Framebuffer* pickFramebuffer, int x, int y){
    pickFramebuffer->bind();
    unsigned char data[3];
    glReadPixels(x,y,1,1, GL_RGB, GL_UNSIGNED_BYTE,data);
    return data[0] + data[1] * 255 + data[2] * 255 * 255;
}

int main() {
    ConfigManager::LoadConfig("project.cfg");

    const unsigned int window_width = static_cast<const unsigned int>(ConfigManager::getFloat("window_width"));
    const unsigned int window_height = static_cast<const unsigned int>(ConfigManager::getFloat("window_height"));
    const unsigned int hex_side = ConfigManager::getFloat("hex_side");
    const char* window_title = ConfigManager::getString("window_title").c_str();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(window_width, window_height, window_title, nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    auto * pickFramebuffer = new Framebuffer(window_width, window_height);
    ClickableSprite::setPickFramebuffer(pickFramebuffer);


    auto marbleTexture = new Texture("marble.jpeg");
    ClickableSprite sprite(marbleTexture, {200, 200}, {0, 0}, angleToMat(0));

    Font arial("arial.ttf");

    float angle = 0;

    HexField field(400, 150, 500, hex_side);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int last_index = 0;
    while(!glfwWindowShouldClose(window)){
        angle+=0.01;
        mat2 rot = angleToMat(angle);
        sprite.setRot(rot);
        sprite.setPos({sin(angle)*200, 0});

        if(keys[GLFW_KEY_ESCAPE])glfwSetWindowShouldClose(window, true);
        if(keysDown[GLFW_KEY_R]){
            if(!frameMode)glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            frameMode = !frameMode;
        }

        double x_pos, y_pos;
        glfwGetCursorPos(window, &x_pos, &y_pos);
        if(x_pos < window_width && y_pos < window_height && x_pos > 0 && y_pos > 0){
            int index = getIndex(pickFramebuffer, static_cast<int>(x_pos), static_cast<int>(window_height - y_pos));
            if(index){
                ClickableSprite::getByIndex(index)->onHover();
                //TODO: check tommorow
                if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)){
                    ClickableSprite::getByIndex(index)->onClick();
                }
            }
            if(index != last_index){
                try{
                    ClickableSprite::getByIndex(last_index)->onHoverOff();
                }
                catch (...){}
            }
            last_index = index;
        }
        else{
            if(last_index)ClickableSprite::getByIndex(last_index)->onHoverOff();
        }

        pickFramebuffer->clear();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        field.render();

        if(field.dirtWon()){
            arial.RenderText("DIRT WON", {500, 0}, 1, {.1, 1.0, .1});
        }
        else if(field.waterWon()){
            arial.RenderText("WATER WON", {500, 0}, 1, {.1, 0.1, 1.0});
        }
        else{
            arial.RenderText("YOUR TURN", {500, 0}, 1, {1.0, 1.0, 1.0});
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }


//    delete button;
    delete marbleTexture;
//    delete label;
    delete pickFramebuffer;
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}