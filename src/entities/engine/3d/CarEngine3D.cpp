//
// Created by daniel on 10/07/23.
//

#include <iostream>
#include "CarEngine3D.h"
#include "../../../gl_canvas2d.h"

CarEngine3D::CarEngine3D(fvec3 position, int speedRPM): speedRPM(speedRPM) {
    crankPosition = position;
    float crankRadius = 50;
    float perspectiveDistance = 250;
    crank = new Crank(crankPosition, speedRPM, perspectiveDistance, crankRadius, 10);

    float initialPistonAngle = 0;
    float rodHeight = 110;
    auto pistonCenter = fvec3{ crankPosition.x, crankPosition.y + crankRadius * cos(initialPistonAngle) + sqrt(rodHeight*rodHeight - crankRadius*crankRadius * sin(initialPistonAngle) * sin(initialPistonAngle)), crankPosition.z };
    piston = new Piston(pistonCenter, speedRPM, perspectiveDistance, 20, 80, rodHeight, initialPistonAngle, crank);

    setRPM(speedRPM);
}

void CarEngine3D::setRPM(int rpm) {
    angularVelocity = PI_2 * rpm / 60;
    crank->setRPM(rpm);
    piston->setRPM(rpm);
}

void CarEngine3D::render(float screenWidth, float screenHeight, float dt) {
    angle += angularVelocity * dt;

    crank->render(screenWidth, screenHeight, dt);
    piston->render(screenWidth, screenHeight, dt);
}

void CarEngine3D::keyboardDown(int key) {
    crank->keyboardDown(key);
    piston->keyboardDown(key);
}

void CarEngine3D::keyboardUp(int key) {
    crank->keyboardUp(key);
    piston->keyboardUp(key);
}
