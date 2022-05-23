#pragma once 
#include <string>

namespace Renderer{

    class Texture
    {
    public:
        Texture(const std::string& filePath);
        void bindTexture(unsigned int slot);
        void unbindTexture();
        unsigned int getTextureID();
        ~Texture() = default;
    private:
        unsigned int textureID = 0;
        unsigned char* localBuffer;
        int textureWidth, textureHeight, textureBBP;
    };

}