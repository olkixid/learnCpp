#ifndef LEARNCPP_RENDERWINDOW_H
#define LEARNCPP_RENDERWINDOW_H

#include <string>
#include <SDL.h>
#include <glad/glad.h>

class Rectangle;
class Texture;

class RenderWindow {
public:
    RenderWindow(const std::string& title, int width, int height);
    ~RenderWindow();
    void clear() { glClearColor(0.0f, 0.0f, 0.0f, 1.0f); glClear(GL_COLOR_BUFFER_BIT); }
    void present() { SDL_GL_SwapWindow(sdlWindow); }
    void draw(const Texture& texture, const Rectangle& src, const Rectangle& dest);

    void draw(const Rectangle& rect);
private:
    SDL_Window* sdlWindow = nullptr;
    SDL_GLContext glContext = nullptr;
    int width;
    int height;

    GLuint vertexShader{0};
    GLuint fragmentShader{0};
    GLuint shaderProg{0};

    GLuint rectVertexShader{0};
    GLuint rectFragmentShader{0};
    GLuint rectShaderProg{0};

    GLuint vao{0};
    GLuint vbo{0};
    GLuint ebo{0};

    GLint matLocation{0};
    GLint texMatLocation{0};
    GLint texLocation{0};

    GLint rectMatLocation{0};
    GLint rectColorLocation{0};

    friend Texture;
};


#endif //LEARNCPP_RENDERWINDOW_H
