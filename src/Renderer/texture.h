#pragma once 
#include <string>

namespace Renderer{

    class Texture
    {
    public:
        Texture(const std::string& filePath);
        void bindTexture(unsigned int slot);
        ~Texture() = default;
    private:
        unsigned int textureID;
        unsigned char* localBuffer;
        int textureWidth, textureHeight, textureBBP;
    };

}