//
// Created by daniel on 10/07/23.
//

#include <iostream>
#include "CarEngine3D.h"
#include "../../../gl_canvas2d.h"

CarEngine3D::CarEngine3D(fvec3 position, int speedRPM): speedRPM(speedRPM) {
    crankPosition = position;
    setRPM(speedRPM);
    crank = new Crank(crankPosition, speedRPM, 180, 50, 10);
}

void CarEngine3D::setRPM(int rpm) {
    angularVelocity = PI_2 * rpm / 60;
}

void CarEngine3D::render(float screenWidth, float screenHeight, float dt) {
    angle += angularVelocity * dt;

    crank->render(screenWidth, screenHeight, dt);
}
