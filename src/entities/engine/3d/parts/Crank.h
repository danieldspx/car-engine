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
    float crankPinRadius;
    int speedRPM, wireframeDivisions, crankPinDivisions;

    v3matrix crankVertices, crankPinVertices, transformedCrankPinVertices;

    Crank(fvec3 center, int speedRPM, float perspectiveDistance, float radius, float depth);

    void render(float screenWidth, float screenHeight, float dt) override;
    void setRPM(int rpm);
    void setPerspectiveDistance(float distance);

    void generateCrankVerticesMatrix();

    void drawCrank();

    void generateCrankPinVerticesMatrix();

    void drawCrankPin();

    fvec3 getTransformedPinCenter();

    Matrix<float> getPinTransformationMatrix();

    fvec2 crankPinUnitVector();
};


#endif //CANVAS_CLION_CRANK_H
