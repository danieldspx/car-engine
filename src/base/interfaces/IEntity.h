//
// Created by daniel on 15/04/23.
//

#ifndef VECTORGRAPHICS_IENTITY_H
#define VECTORGRAPHICS_IENTITY_H

#include "IRender.h"
#include "IMouse.h"
#include "IIntersect.h"
#include "IKeyboard.h"

class IEntity: public IKeyboard, public IRender, public IIntersect {
public:
    float r, g, b;
    void changeToRandomColor() {
        r = rand() % 255;
        g = rand() % 255;
        b = rand() % 255;
    };
    void setToColor(float _r, float _g, float _b) {
        r = _r;
        g = _g;
        b = _b;
    };
};

#endif //VECTORGRAPHICS_IENTITY_H
