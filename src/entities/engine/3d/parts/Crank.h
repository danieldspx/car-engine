//
// Created by daniel on 10/07/23.
//

#ifndef CANVAS_CLION_CRANK_H
#define CANVAS_CLION_CRANK_H


#include "../../../../base/interfaces/IRender.h"
#include "../../../../base/vectors/Vector2D.h"
#include "../../../../base/vectors/Vector3D.h"
#include "../../../../base/vectors/Matrix.h"

class Crank: IRender {
public:
    fvec3 center;
    float radius, depth, rollAngle, angularVelocity, perspectiveDistance;
    int speedRPM;

    v3matrix crankVertices;

    Crank(fvec3 center, int speedRPM, float perspectiveDistance, float radius, float depth);

    void render(float screenWidth, float screenHeight, float dt) override;
    void setRPM(int rpm);
    void setPerspectiveDistance(float distance);

    void generateVerticesMatrix();

    void drawCrank();
};


#endif //CANVAS_CLION_CRANK_H
