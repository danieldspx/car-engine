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
        rodSides = 10;
        rodRadius = 8;
        setRPM(speedRPM);
        generatePistonVertices();
        // Each row stores the points of the rod, the first row is the first rod-shape points
        // in the bottom and the last row is the last rod-shape points in the top
        rodVertices = Matrix<fvec3>(wireframeDivisions, rodSides);
}

void Piston::render(float screenWidth, float screenHeight, float dt) {
    drawPiston();
    drawConnectingRod();
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
            pistonVertices[row][i] = fvec3{center.x + radius * cos(angAcc), center.y + row * heightIncr - height, center.z  + radius * sin(angAcc) };

            angAcc += circleAngIcre;
        }
    }
}

void Piston::generateRodVertices() {
    auto crankPinCenter = crankInstance->getTransformedPinCenter();
    auto pistonCenter = center + fvec3{0,getYChangeBasedOnPin() - height / 2,0};

    // Going from crankPinCenter to pistonCenter
    auto totalSteps = rodVertices.rows - 1;
    auto stepX = (pistonCenter.x - crankPinCenter.x) / totalSteps;
    auto stepY = (pistonCenter.y - crankPinCenter.y) / totalSteps;
    auto stepZ = (pistonCenter.z - crankPinCenter.z) / totalSteps;

    float circleAngIcre = PI_2 / rodSides;
    for (int row = 0; row < rodVertices.rows; row++) {
        float angAcc = 0;
        for (int i = 0; i < rodVertices.cols; i++) {
            rodVertices[row][i] = fvec3{
                crankPinCenter.x + stepX * row + rodRadius * cos(angAcc),
                crankPinCenter.y + stepY * row,
                crankPinCenter.z + stepZ * row + rodRadius * sin(angAcc)
            };
            angAcc += circleAngIcre;
        }
    }
}

/**
 * Updates the piston Y coordinate according to the crank pin position
 * since they are attached
 */
Matrix<Vector3D<float>> Piston::getTransformedPistonVertices() {
    auto transformedPistonVertices = pistonVertices.clone();
    auto deltaY = getYChangeBasedOnPin();
    for (int row = 0; row < pistonVertices.rows; row++) {
        for (int i = 0; i < pistonVertices.cols; i++) {
            transformedPistonVertices[row][i].y += deltaY;
        }
    }

    return transformedPistonVertices;
}

float Piston::getYChangeBasedOnPin() {
    auto pinVector = crankInstance->crankPinUnitVector();
    fvec2 baseY = {0, 1};
    auto anglePistonCrank = baseY.angle(pinVector);
//    printf("\n[3D]Angle Piston Crank: %f", anglePistonCrank * 180 / PI);
    auto crankRadius = crankInstance->radius;

    // Position equation: https://en.wikipedia.org/wiki/Piston_motion_equations
    return crankRadius * cos(anglePistonCrank) + sqrt(rodHeight*rodHeight - crankRadius*crankRadius * sin(anglePistonCrank) * sin(anglePistonCrank));
}

void Piston::drawConnectingRod() {
    CV::color(87, 87, 87);

    generateRodVertices();
    for (int row = 0; row < rodVertices.rows; row++) {
        for (int i = 0; i < rodVertices.cols; i++) {
            auto currentVertex = rodVertices[row][i];
            auto nextVertexOnLine = rodVertices[row][(i + 1) % rodVertices.cols];

            CV::line(currentVertex.toPerspective(perspectiveDistance), nextVertexOnLine.toPerspective(perspectiveDistance));
        }
    }

    for (int i = 0; i < rodVertices.cols; i++) {
        auto bottomVertex = rodVertices[0][i];
        auto topVertex = rodVertices[rodVertices.cols - 1][i];

        CV::line(bottomVertex.toPerspective(perspectiveDistance), topVertex.toPerspective(perspectiveDistance));
    }
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


