//
// Created by daniel on 10/07/23.
//

#ifndef CANVAS_CLION_CARENGINE2D_H
#define CANVAS_CLION_CARENGINE2D_H


#include "../../../base/interfaces/IKeyboard.h"
#include "../../../base/interfaces/IRender.h"

class CarEngine2D: public IRender, public IKeyboard {
private:
    float angle, angularVelocity;
    int speedRPM;
    fvec2 crankPosition;
public:
    explicit CarEngine2D(fvec2 position, int speedRPM);

    void keyboardDown(int key) override;

    void keyboardUp(int key) override;

    void render(float screenWidth, float screenHeight, float dt) override;

    void setRPM(int rpm);
};


#endif //CANVAS_CLION_CARENGINE2D_H
