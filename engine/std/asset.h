//
//  asset.hpp
//  GLESEngine
//
//  Created by 彭怀亮 on 6/8/19.
//  Copyright © 2019 彭怀亮. All rights reserved.
//


/*
 资源管理器 配合工具使用
*/

#ifndef asset_h
#define asset_h


#include "../common.h"

namespace engine
{
    
    #define PNG   0x0010  //.png
    #define JPG   0x0020  //.jpg
    #define TGA   0x0030  //.tga
    #define BMP   0x0040  //.bmp
    #define HDR   0x0050  //.hdr

    #define FBX   0x0001 //.fbx
    #define MTL   0x0002 //.mtl
    #define OBJ   0x0003 //.obj
    #define ANIM  0x0004 //.anim
    #define TTF   0x0005 //.ttf
    
    #define SUM   0x0100 //.sum
    #define MESH  0x0200 //.mesh
    #define MAT   0x0300 //.mat

    extern std::map<unsigned int,int> asset_map;
    
    bool initial();
    
    bool isTexure(int ext);
    
    bool isEngineAsset(int ext);
     
    std::string getResPath(std::string path);
    
    
}




#endif /* asset_hpp */
