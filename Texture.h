#ifndef LEARNCPP_TEXTURE_H
#define LEARNCPP_TEXTURE_H

#include <glad/glad.h>

#include <boost/filesystem.hpp>
#include <utility>

class RenderWindow;

class Texture {
public:
    Texture() = default;
    Texture(Texture&& tex) noexcept : texture{tex.texture}, mw{tex.mw}, mh{tex.mh} {
        tex.texture = 0;
    }
    Texture& operator=(Texture&& tex) {
        std::swap(texture, tex.texture);
        std::swap(mw, tex.mw);
        std::swap(mh, tex.mh);
        return *this;
    }
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture(const boost::filesystem::path& imagePath, const RenderWindow& contextRenderer);
    ~Texture();

    void load(const boost::filesystem::path& imagePath, const RenderWindow& contextRenderer);

    float w() const { return mw; }
    float h() const { return mh; }
private:
    GLuint texture{0};

    float mw{0.f};
    float mh{0.f};

    friend RenderWindow;
};


#endif //LEARNCPP_TEXTURE_H
