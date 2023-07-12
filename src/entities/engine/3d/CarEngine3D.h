//
// Created by daniel on 10/07/23.
//

#ifndef CANVAS_CLION_CARENGINE3D_H
#define CANVAS_CLION_CARENGINE3D_H

#include "../../../base/interfaces/IRender.h"
#include "../../../base/vectors/Vector2D.h"
#include "parts/Crank.h"
#include "parts/Piston.h"
#include "../../../base/interfaces/IKeyboard.h"

class CarEngine3D: public IRender, public IKeyboard {
private:
    float angle, angularVelocity;
    int speedRPM;
    fvec3 crankPosition;

    Crank* crank;
    Piston* piston;
public:
    CarEngine3D(fvec3 position, int speedRPM, float perspectiveDistance);

    void render(float screenWidth, float screenHeight, float dt) override;

    void setRPM(int rpm);

    void keyboardDown(int key) override;

    void keyboardUp(int key) override;

    void setPerspectiveDistance(float distance);
    void setOrthoMode();
};


#endif //CANVAS_CLION_CARENGINE3D_H
