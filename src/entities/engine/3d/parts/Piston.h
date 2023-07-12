//
// Created by daniel on 10/07/23.
//

#ifndef CANVAS_CLION_PISTON_H
#define CANVAS_CLION_PISTON_H


#include "../../../../base/interfaces/IRender.h"
#include "../../../../base/vectors/Vector2D.h"
#include "../../../../base/vectors/Vector3D.h"

class Piston: IRender {
public:
    fvec3 center;
    float radius, height, angularVelocity, perspectiveDistance, angle, rodHeight, rodWidth;
    int speedRPM, wireframeDivisions;

    // The crank this piston is attached
    Crank* crankInstance;

    v3matrix pistonVertices;

    Piston(fvec3 center, int speedRPM, float perspectiveDistance, float radius, float height, float rodHeight, float initAngle, Crank* crankInstance);

    void render(float screenWidth, float screenHeight, float dt) override;
    void setRPM(int rpm);

    void generatePistonVertices();

    void drawPiston();

    Matrix<Vector3D<float>> getTransformedPistonVertices();
};


#endif //CANVAS_CLION_PISTON_H