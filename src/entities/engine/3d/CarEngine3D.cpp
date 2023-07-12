//
// Created by daniel on 10/07/23.
//

#include <iostream>
#include "CarEngine3D.h"
#include "../../../gl_canvas2d.h"

CarEngine3D::CarEngine3D(fvec3 position, int speedRPM): speedRPM(speedRPM) {
    crankPosition = position;
    setRPM(speedRPM);
    float crankRadius = 60;
    crank = new Crank(crankPosition, speedRPM, 180, crankRadius, 10);

    float initialPistonAngle = 0;
    float rodHeight = 100;
    auto pistonCenter = fvec3{ crankPosition.x, crankPosition.y + crankRadius * cos(initialPistonAngle) + sqrt(rodHeight*rodHeight - crankRadius*crankRadius * sin(initialPistonAngle) * sin(initialPistonAngle)), crankPosition.z };
    piston = new Piston(pistonCenter, speedRPM, 180, 20, 100, rodHeight, initialPistonAngle, crank);
}

void CarEngine3D::setRPM(int rpm) {
    angularVelocity = PI_2 * rpm / 60;
}

void CarEngine3D::render(float screenWidth, float screenHeight, float dt) {
    angle += angularVelocity * dt;

    crank->render(screenWidth, screenHeight, dt);
    piston->render(screenWidth, screenHeight, dt);
}
