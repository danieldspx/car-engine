//
// Created by daniel on 12/04/23.
//

#ifndef VECTORGRAPHICS_IRENDER_H
#define VECTORGRAPHICS_IRENDER_H

class IRender {
public:
    virtual void render(float screenWidth, float screenHeight, float dt, float baseHeight = 0) {};
    virtual void render(float screenWidth, float screenHeight, float dt) {};
};

#endif
