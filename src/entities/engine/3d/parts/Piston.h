//
// Created by daniel on 10/07/23.
//

#ifndef CANVAS_CLION_PISTON_H
#define CANVAS_CLION_PISTON_H


#include "../../../../base/interfaces/IRender.h"
#include "../../../../base/vectors/Vector2D.h"
#include "../../../../base/vectors/Vector3D.h"
#include "../../../../base/interfaces/IKeyboard.h"

class Piston: public IRender, public IKeyboard {
public:
    fvec3 center;
    float radius, height, angularVelocity, perspectiveDistance, angle, yawAngle, pitchAngle, rodHeight, rodRadius;
    int speedRPM, wireframeDivisions, rodSides;

    bool rotateX = false; // Key 120
    bool rotateY = false; // Key 121

    void keyboardDown(int key) override;

    void keyboardUp(int key) override;

    // The crank this piston is attached
    Crank* crankInstance;

    v3matrix pistonVertices, rodVertices;

    Piston(fvec3 center, int speedRPM, float perspectiveDistance, float radius, float height, float rodHeight, float initAngle, Crank* crankInstance);

    void render(float screenWidth, float screenHeight, float dt) override;
    void setRPM(int rpm);

    void generatePistonVertices();

    void drawPiston();

    Matrix<Vector3D<float>> getTransformedPistonVertices();

    void drawConnectingRod();

    void generateRodVertices();

    float getYChangeBasedOnPin();

    void setPerspectiveDistance(float distance);

    Matrix<Vector3D<float>> getTransformedRodVertices();
};


#endif //CANVAS_CLION_PISTON_H
