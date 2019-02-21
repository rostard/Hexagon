cmake_minimum_required(VERSION 3.12)
project(Hexagon)




set(CMAKE_CXX_STANDARD 17)

add_executable(Hexagon src/main.cpp src/dependencies/glad.c src/Sprite.cpp src/Sprite.h src/math.cpp src/math.h src/Shader.cpp src/Shader.h src/Texture.cpp src/Texture.h src/common.h src/common.cpp src/ConfigManager.cpp src/ConfigManager.h src/dependencies/stb_image.cpp src/gui/GUIObject.cpp src/gui/GUIObject.h src/gui/GUIButton.cpp src/gui/GUIButton.h src/gui/Font.cpp src/gui/Font.h src/gui/GUILabel.cpp src/gui/GUILabel.h src/gui/GUITree.cpp src/gui/GUITree.h  src/Framebuffer.cpp src/Framebuffer.h src/ClickableSprite.cpp src/ClickableSprite.h src/HexField.cpp src/HexField.h src/Hexagon.cpp src/Hexagon.h src/Game.cpp src/Game.h)

target_link_libraries(${PROJECT_NAME} -L/usr/local/lib -I/usr/include/freetype2 -I/usr/include/libdrm -lGL
        -lfreetype -lz -lm -lglfw -lrt -ldl -lXrandr -lXxf86vm -lXext  -lXrender -lXfixes -lX11 -lpthread -lxcb -lXau -lassimp -lstdc++)