#include <iostream>
#include "texture.h"
#include <glad/glad.h>
#include "../fromGit/stb_image.h"

namespace Renderer{

Texture::Texture(const std::string& filePath)
                :localBuffer(nullptr), textureBBP(0), 
                textureWidth(0), textureHeight(0),
                textureID(0){
    localBuffer = stbi_load(filePath.c_str(), &textureWidth, &textureHeight, &textureBBP, 4);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if(localBuffer){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);
    }else{
        std::cerr<< "Unable to load texture" <<std::endl;
    }

    stbi_image_free(localBuffer);
}

void Texture::bindTexture(unsigned int slot){
    //glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, textureID);
}


}