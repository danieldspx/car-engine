//
// Created by daniel on 10/07/23.
//

#ifndef CANVAS_CLION_CARENGINE3D_H
#define CANVAS_CLION_CARENGINE3D_H

#include "../../../base/interfaces/IRender.h"
#include "../../../base/vectors/Vector2D.h"
#include "parts/Crank.h"

class CarEngine3D: public IRender {
private:
    float angle, angularVelocity;
    int speedRPM;
    fvec3 crankPosition;

    Crank* crank;
public:
    CarEngine3D(fvec3 position, int speedRPM);

    void render(float screenWidth, float screenHeight, float dt) override;

    void setRPM(int rpm);
};


#endif //CANVAS_CLION_CARENGINE3D_H
