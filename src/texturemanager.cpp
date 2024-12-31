#define STB_IMAGE_IMPLEMENTATION
#include "texturemanager.hpp"
#include<glad/glad.h>
#include <stb/stb_image.h>

namespace graf
{
    TextureManager* TextureManager::m_Instance = nullptr;

    TextureManager::TextureManager()
    {
        
    }


    TextureManager* TextureManager::getInstance()
    {
        if(m_Instance==nullptr)
        {
            m_Instance = new TextureManager();
        }
        return m_Instance;
    }


    void TextureManager::addTextureFromFile(const string& fileName)
    {
        auto manager = getInstance();
        string fullFileName = "./images/"+fileName;
        if(manager->m_TextureMap.count(fileName)>0)
        {
            return ;
        }

        int width,height,channels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(fullFileName.data(),&width,&height,&channels,0);

        unsigned int texture;
        glGenTextures(1,&texture);
        glBindTexture(GL_TEXTURE_2D,texture);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);

        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);

        getInstance()->m_TextureMap[fileName] = texture;

    }
    void TextureManager::activateTexture(const string& fileName)
    {
        auto manager = getInstance();

        if(manager->m_TextureMap.count(fileName)<=0)
        {
            return ;
        }

        unsigned int id = manager->m_TextureMap[fileName];

        glBindTexture(GL_TEXTURE_2D,id);

    }

}