//
//  texture.cpp
//  OpenGLEngine
//
//  Created by 彭怀亮 on 5/29/19.
//  Copyright © 2019 彭怀亮. All rights reserved.
//

#include "texture.h"
#include <iostream>
#include "texmgr.h"
#ifdef _GLES_
#include "FilePath.h"
#else
#include "../ext/stb_image.h"
#endif
#include "profile.h"

namespace engine
{

    Texture::Texture(const char* path, EXT ext, GLuint* texID, bool flipY, int wrap)
    {
        std::string spath(path);
        spath = getResPath(spath + getTextureExt(ext));
        this->path=spath.c_str();
        *texID = LoadTexture(flipY, ext, wrap);
    }


    Texture::~Texture()
    {
        TexMgr::getInstance()->RemvTexture(textureID);
    }

    GLuint Texture::LoadTexture(bool flipY, EXT ext,int wrap)
    {
    #ifndef _GLES_
        stbi_set_flip_vertically_on_load(flipY);
    #endif
        
        glCheckError();
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
#ifdef _GLES_
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#else
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#endif
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        
        GLenum glformat = GL_RGBA;
        unsigned char* data = nullptr;
        GLint level = 0;
        int bitsPerPixel =0;
    #ifndef _GLES_
        data = stbi_load(path, &width, &height, &format, 0);
    #else
        if (ext == PVR)
            data = LoadPvr(path, &width, &height, &glformat, &level, &bitsPerPixel);
        else if(ext == TGA)
            data = LoadTGA(NULL, path, &width, &height, glformat);
        else
            data = LoadImage(std::string(path), getTextureExt(ext), &width,  &height);
    #endif
        if (data)
        {
    #ifndef _GLES_
            GLenum glformat = GetFormat();
    #endif
            
            glCheckError();
            if(ext == PVR)
            {
                for (int mip = 0; mip < level; ++mip) {
                    GLsizei size = max(32, width * height * bitsPerPixel / 8);
                    glCompressedTexImage2D(GL_TEXTURE_2D, mip, glformat, width, height, 0, size, data);
                    glCheckError();
                    data += size;
                    width >>= 1; height >>= 1;
                }
            }
            else
            {
                glTexImage2D(GL_TEXTURE_2D, 0, glformat, width, height, 0, glformat, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
        }
        else
        {
            std::cout << "Texture failed: " << path << std::endl;
        }
    #ifndef _GLES_
        stbi_image_free(data);
    #else
        if (ext == PVR)
            UnloadPvr();
        else
            free(data);
    #endif
        return textureID;
    }

    ivec2 Texture::GetShape()
    {
        return ivec2(width,height);
    }

    GLenum Texture::GetFormat()
    {
        GLenum glformat;
        if (this->format == 1)
            glformat = GL_RED;
        else if (this->format == 3)
            glformat = GL_RGB;
        else if (this->format == 4)
            glformat = GL_RGBA;
        else
        {
            glformat = GL_RED;
            std::cout<<"texture is not support the format"<<this->format<<std::endl;
        }
        return glformat;
    }

}
