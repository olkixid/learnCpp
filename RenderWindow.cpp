#include "RenderWindow.h"

#include "Rectangle.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>


const char *vertexShaderSource = "#version 410 core\n"
                                 "layout (location = 0) in vec2 aPos;\n"
                                 "out vec2 texCoords;\n"
                                 "uniform mat3 posMat;\n"
                                 "uniform mat3 texMat;\n"
                                 "void main()\n"
                                 "{\n"
                                 "    vec3 pos = posMat * vec3(aPos.x, aPos.y, 1.0);\n"
                                 "    gl_Position = vec4(pos.x, pos.y, 0.0, 1.0);\n"
                                 "    texCoords = vec2(texMat * vec3(aPos, 1.0));\n"
                                 "}";

const char *fragmentShaderSource = "#version 410 core\n"
                                   "layout (location = 0) out vec4 FragColor;\n"
                                   "in vec2 texCoords;\n"
                                   "uniform sampler2D tex;\n"
                                   "void main()\n"
                                   "{\n"
                                   "    FragColor = texture(tex, texCoords);\n"
                                   "}\n";


const char *rectVertexShaderSource = "#version 410 core\n"
                                     "layout (location = 0) in vec2 aPos;\n"
                                     "uniform mat3 posMat;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    vec3 pos = posMat * vec3(aPos.x, aPos.y, 1.0);\n"
                                     "    gl_Position = vec4(pos.x, pos.y, 0.0, 1.0);\n"
                                     "}";

const char *rectFragmentShaderSource = "#version 410 core\n"
                                       "layout (location = 0) out vec4 FragColor;\n"
                                       "in vec2 texCoords;\n"
                                       "uniform vec3 rectColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "    FragColor = vec4(rectColor, 1.0);\n"
                                       "}\n";


RenderWindow::RenderWindow(const std::string& title, int width, int height)
: width{width},
  height{height}
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    sdlWindow = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    glContext = SDL_GL_CreateContext(sdlWindow);

    gladLoadGLLoader(SDL_GL_GetProcAddress);



    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    GLint success = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    std::cout << success << std::endl;

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    std::cout << success << std::endl;

    shaderProg = glCreateProgram();
    glAttachShader(shaderProg, vertexShader);
    glAttachShader(shaderProg, fragmentShader);
    glLinkProgram(shaderProg);

    glGetProgramiv(shaderProg, GL_LINK_STATUS, &success);
    std::cout << success << std::endl;

    glGetProgramiv(shaderProg, GL_INFO_LOG_LENGTH, &success);
    std::cout << success << std::endl;

    char info[500];
    glGetProgramInfoLog(shaderProg, sizeof(info), nullptr, info);

    std::cout << info << std::endl;

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    matLocation = glGetUniformLocation(shaderProg, "posMat");
    texMatLocation = glGetUniformLocation(shaderProg, "texMat");
    texLocation = glGetUniformLocation(shaderProg, "tex");



    rectVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(rectVertexShader, 1, &rectVertexShaderSource, NULL);
    glCompileShader(rectVertexShader);
    success = 0;
    glGetShaderiv(rectVertexShader, GL_COMPILE_STATUS, &success);
    std::cout << success << std::endl;

    rectFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(rectFragmentShader, 1, &rectFragmentShaderSource, NULL);
    glCompileShader(rectFragmentShader);

    glGetShaderiv(rectFragmentShader, GL_COMPILE_STATUS, &success);
    std::cout << success << std::endl;

    rectShaderProg = glCreateProgram();
    glAttachShader(rectShaderProg, rectVertexShader);
    glAttachShader(rectShaderProg, rectFragmentShader);
    glLinkProgram(rectShaderProg);

    glGetProgramiv(rectShaderProg, GL_LINK_STATUS, &success);
    std::cout << success << std::endl;

    glGetProgramiv(rectShaderProg, GL_INFO_LOG_LENGTH, &success);
    std::cout << success << std::endl;

    //char info[500];
    glGetProgramInfoLog(rectShaderProg, sizeof(info), nullptr, info);

    std::cout << info << std::endl;

    glDeleteShader(rectVertexShader);
    glDeleteShader(rectFragmentShader);

    rectMatLocation = glGetUniformLocation(rectShaderProg, "posMat");
    rectColorLocation = glGetUniformLocation(rectShaderProg, "rectColor");



    float vertices[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
    };
    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);


    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);


    glBindVertexArray(0);
}

RenderWindow::~RenderWindow() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    glDeleteProgram(shaderProg);
    glDeleteProgram(rectShaderProg);

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(sdlWindow);
}


void RenderWindow::draw(const Rectangle &rect) {
    glm::mat3 scaleMat {
            rect.w(), 0.f,     0.f,
            0.f,     rect.h(), 0.f,
            0.f,     0.f,      1.f
    };

    glm::mat3 translateMat {
            1.f,      0.f,      0.f,
            0.f,      1.f,      0.f,
            rect.x(), rect.y(), 1.f
    };

    glm::mat3 cameraMat {
            2.f / static_cast<float>(width), 0.f,                              0.f,
            0.f,                             2.f / static_cast<float>(height), 0.f,
            -1.f,                            -1.f,                              1.f
    };

    glUseProgram(rectShaderProg);
    glBindVertexArray(vao);

    glUniformMatrix3fv(rectMatLocation, 1, false, glm::value_ptr(cameraMat * translateMat * scaleMat));
    glUniform3f(rectColorLocation, 1.f, 0.f, 0.f);

    glDrawElements(GL_LINE_STRIP, 6, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
}

void RenderWindow::draw(const Texture& texture, const Rectangle& src, const Rectangle &dest) {
    constexpr glm::mat3 flipTexMat {
        1.f,  0.f, 0.f,
        0.f, -1.f, 0.f,
        0.f,  1.f, 1.f
    };

    glm::mat3 scaleTexMat {
        src.w() / texture.w(), 0.f,                   0.f,
        0.f,                   src.h() / texture.h(), 0.f,
        0.f,                   0.f,                   1.f
    };

    glm::mat3 translateTexMat {
        1.f,                   0.f,                   0.f,
        0.f,                   1.f,                   0.f,
        src.x() / texture.w(), src.y() / texture.h(), 1.f
    };

    glm::mat3 scaleMat {
        dest.w(), 0.f,     0.f,
        0.f,     dest.h(), 0.f,
        0.f,     0.f,      1.f
    };

    glm::mat3 translateMat {
        1.f,      0.f,      0.f,
        0.f,      1.f,      0.f,
        dest.x(), dest.y(), 1.f
    };

    glm::mat3 cameraMat {
        2.f / static_cast<float>(width), 0.f,                              0.f,
        0.f,                             2.f / static_cast<float>(height), 0.f,
        -1.f,                            -1.f,                              1.f
    };

    glUseProgram(shaderProg);
    glBindVertexArray(vao);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.texture);
    glUniform1i(texLocation, 0);

    glUniformMatrix3fv(matLocation, 1, false, glm::value_ptr(cameraMat * translateMat * scaleMat));
    glUniformMatrix3fv(texMatLocation, 1, false, glm::value_ptr(translateTexMat * scaleTexMat * flipTexMat));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
}
