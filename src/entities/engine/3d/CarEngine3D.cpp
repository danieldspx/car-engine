//
// Created by daniel on 10/07/23.
//

#include <iostream>
#include "CarEngine3D.h"
#include "../../../gl_canvas2d.h"

CarEngine3D::CarEngine3D(fvec3 position, int speedRPM, float perspectiveDistance): speedRPM(speedRPM) {
    crankPosition = position;
    float crankRadius = 50;
    crank = new Crank(crankPosition, speedRPM, perspectiveDistance, crankRadius, 10);

    float initialPistonAngle = 0;
    float rodHeight = 110;
    float angleBetweenPistons = 80;
    float distanceFromCenter = sqrt(2*rodHeight*rodHeight * (1 - cos(angleBetweenPistons*PI/180)))/2;
    auto pistonsCenter = fvec3{ crankPosition.x, crankPosition.y + crankRadius * cos(initialPistonAngle) + sqrt(rodHeight*rodHeight - crankRadius*crankRadius * sin(initialPistonAngle) * sin(initialPistonAngle)), crankPosition.z };
    piston = new Piston(pistonsCenter - fvec3 {distanceFromCenter, 0, 0}, speedRPM, perspectiveDistance, 20, 80, rodHeight, initialPistonAngle, crank);
    piston2 = new Piston(pistonsCenter + fvec3 {distanceFromCenter, 0, 0}, speedRPM, perspectiveDistance, 20, 80, rodHeight, initialPistonAngle, crank);

    setRPM(speedRPM);
}

void CarEngine3D::setRPM(int rpm) {
    angularVelocity = PI_2 * rpm / 60;
    crank->setRPM(rpm);
    piston->setRPM(rpm);
    piston2->setRPM(rpm);
}

void CarEngine3D::render(float screenWidth, float screenHeight, float dt) {
    angle += angularVelocity * dt;

    crank->render(screenWidth, screenHeight, dt);
    piston->render(screenWidth, screenHeight, dt);
    piston2->render(screenWidth, screenHeight, dt);
}

void CarEngine3D::keyboardDown(int key) {
    crank->keyboardDown(key);
    piston->keyboardDown(key);
    piston2->keyboardDown(key);
}

void CarEngine3D::keyboardUp(int key) {
    crank->keyboardUp(key);
    piston->keyboardUp(key);
    piston2->keyboardUp(key);
}

void CarEngine3D::setPerspectiveDistance(float distance) {
    crank->setPerspectiveDistance(distance);
    piston->setPerspectiveDistance(distance);
    piston2->setPerspectiveDistance(distance);
}

void CarEngine3D::setOrthoMode() {
    // -1 will make the toPerspectiveOrOrtho to use the Ortho projection
    setPerspectiveDistance(-1);
}
