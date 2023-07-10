//
// Created by daniel on 14/04/23.
//

#ifndef VECTORGRAPHICS_IKEYBOARD_H
#define VECTORGRAPHICS_IKEYBOARD_H

#include "../vectors/Vector2D.h"

class IKeyboard {
public:
    virtual void keyboardDown(int key) = 0;
    virtual void keyboardUp(int key) = 0;
};

#endif //VECTORGRAPHICS_IKEYBOARD_H
