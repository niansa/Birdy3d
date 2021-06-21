#pragma once

#include "render/Color.hpp"
#include <glad/glad.h>
#include <string>

namespace Birdy3d {

    class Texture {
    public:
        unsigned int id;
        int width, height, nrChannels;

        Texture(unsigned int width, unsigned int height, GLenum format, GLenum internalFormat, GLenum pixelType);
        Texture(const std::string& filePath);
        Texture(const Color& color);
        ~Texture();
        bool transparent();

    private:
        bool m_transparent;
    };

}
