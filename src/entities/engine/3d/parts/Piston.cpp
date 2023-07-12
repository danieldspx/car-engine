//
// Created by daniel on 10/07/23.
//

#include "Crank.h"
#include "../../../../gl_canvas2d.h"
#include "Piston.h"

/**
 * Radius is in the xy plane and depth is the z component to add when generating the vertices
 */
Piston::Piston(fvec3 center, int speedRPM, float perspectiveDistance, float radius, float height, float rodHeight, float initAngle, Crank* crankInstance):
    center(center), speedRPM(speedRPM), perspectiveDistance(perspectiveDistance), radius(radius), height(height), rodHeight(rodHeight), crankInstance(crankInstance) {
        wireframeDivisions = 10;
        angle = initAngle;
        rodWidth = 15;
        setRPM(speedRPM);
        generatePistonVertices();
}

void Piston::render(float screenWidth, float screenHeight, float dt) {
    drawPiston();
}

void Piston::setRPM(int rpm) {
    angularVelocity = PI_2 * rpm / 60;
}

void Piston::generatePistonVertices() {
    // Each row stores the points of a circle, the first row is the first circle
    // in the bottom and the last row is the last circle in the top
    pistonVertices = Matrix<fvec3>(wireframeDivisions, wireframeDivisions);

    float circleAngIcre = PI_2 / wireframeDivisions;
    float heightIncr = height / wireframeDivisions;
    for (int row = 0; row < pistonVertices.rows; row++) {
        float angAcc = 0;
        for (int i = 0; i < wireframeDivisions; i++) {
            pistonVertices[row][i] = fvec3{center.x + radius * cos(angAcc), center.y + row * heightIncr, center.z  + radius * sin(angAcc) };

            angAcc += circleAngIcre;
        }
    }
}

/**
 * Updates the piston Y coordinate acoording to the crank pin position
 * since they are attached
 */
Matrix<Vector3D<float>> Piston::getTransformedPistonVertices() {
    auto pinCenter = crankInstance->getTransformedPinCenter();
    fvec3 baseY = {0, 1, 0};
    printf("\n Pin Center: (%f, %f, %f)", pinCenter.x, pinCenter.y, pinCenter.z);
    auto transformedPistonVertices = pistonVertices.clone();
    auto anglePistonCrank = baseY.angle(pinCenter);
    printf("\nAngle: %f", anglePistonCrank);
    auto crankRadius = crankInstance->radius;
    for (int row = 0; row < pistonVertices.rows; row++) {
        for (int i = 0; i < pistonVertices.cols; i++) {
            // Position equation: https://en.wikipedia.org/wiki/Piston_motion_equations
            transformedPistonVertices[row][i].y += crankRadius * cos(anglePistonCrank) + sqrt(rodHeight*rodHeight - crankRadius*crankRadius * sin(anglePistonCrank) * sin(anglePistonCrank));
        }
    }

    return transformedPistonVertices;
}

void Piston::drawPiston() {
    CV::color(87, 87, 87);
    auto transformedVertices = getTransformedPistonVertices();
    for (int row = 0; row < transformedVertices.rows; row++) {
        for (int i = 0; i < transformedVertices.cols; i++) {
            auto currentVertex = transformedVertices[row][i];
            auto nextVertexOnLine = transformedVertices[row][(i + 1) % transformedVertices.cols];

            CV::line(currentVertex.toPerspective(perspectiveDistance), nextVertexOnLine.toPerspective(perspectiveDistance));
        }
    }

    for (int i = 0; i < transformedVertices.cols; i++) {
        auto bottomVertex = transformedVertices[0][i];
        auto topVertex = transformedVertices[transformedVertices.cols - 1][i];

        CV::line(bottomVertex.toPerspective(perspectiveDistance), topVertex.toPerspective(perspectiveDistance));
    }
}


