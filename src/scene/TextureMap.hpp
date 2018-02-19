//
// Created by Zaiyang Li on 31/01/2018.
//

#ifndef RENDERER_TEXTUREMAP_HPP
#define RENDERER_TEXTUREMAP_HPP

namespace {
    class TextureMap {
        int width;
        int height;
        int bitsPerChannel;
        int channels;
        char* data;

        ~TextureMap() {
            if(data != nullptr) {
                delete data;
            }
        }
    };
}


#endif //RENDERER_TEXTUREMAP_HPP
