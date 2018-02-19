//
// Created by Zaiyang Li on 31/01/2018.
//

#include "RenderTarget.hpp"

McRenderer::RenderTarget::~RenderTarget() {

}

McRenderer::RenderTarget::RenderTarget(int widthIn, int heightIn)
        : width{widthIn}, height{heightIn} {
    if(width < 1 || height < 1) {
        throw 1;
    }
    
}

void McRenderer::RenderTarget::setColor(int x, int y, glm::vec3 colour) {

}
