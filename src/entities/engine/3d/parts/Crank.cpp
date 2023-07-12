//
// Created by daniel on 10/07/23.
//

#include "Crank.h"
#include "../../../../gl_canvas2d.h"

/**
 * Radius is in the xy plane and depth is the z component to add when generating the vertices
 */
Crank::Crank(fvec3 center, int speedRPM, float perspectiveDistance, float radius, float depth): center(center), speedRPM(speedRPM), radius(radius), depth(depth), perspectiveDistance(perspectiveDistance) {
    rollAngle = 0;
    wireframeDivisions = 40;
    crankPinRadius = 30;
    setRPM(speedRPM);
    generateCrankVerticesMatrix();
    generateCrankPinVerticesMatrix();
}

void Crank::render(float screenWidth, float screenHeight, float dt) {
    rollAngle += angularVelocity * dt;
    drawCrank();
    drawCrankPin();
}

void Crank::setRPM(int rpm) {
    angularVelocity = PI_2 * rpm / 60;
}

void Crank::generateCrankVerticesMatrix() {
    int divisions = wireframeDivisions;
    // Each row stores a position of the crank and the column is 0 for front and 1 for back
    crankVertices = Matrix<fvec3>(divisions, 2);
    std::cout << "Crank Initial Position: ";
    center.print();
    float incr = PI_2/divisions;
    float ang = 0;
    for (int i = 0; i < divisions; i++) {
        crankVertices.m[i][0] = fvec3{ center.x + radius * cos(ang), center.y + radius * sin(ang), center.z };
        crankVertices.m[i][1] = fvec3{ center.x + radius * cos(ang), center.y + radius * sin(ang), center.z + depth };
        ang += incr;
    }
}

void Crank::drawCrank() {
    CV::color(173, 173, 173);

    Matrix<fvec3> transformedVertices(crankVertices.rows, crankVertices.cols);

    auto translateOrigin = Matrix<float>::translate(center * -1);
    auto rotateZ = Matrix<float>::rotateZ(rollAngle);
    auto translateCenter = Matrix<float>::translate(center);

    auto transfMatrix = translateCenter * rotateZ * translateOrigin;

    for (int i = 0; i < crankVertices.rows; i++) {
        for (int j = 0; j < crankVertices.cols; j++) {
            auto transformedVertex = transfMatrix * crankVertices[i][j].toVector4(1);
            transformedVertices[i][j] = transformedVertex.toVector3();
        }
    }

    for (int r = 0; r < transformedVertices.rows; r++) {
        auto pFront = transformedVertices.m[r][0].toPerspective(perspectiveDistance);
        auto pBack = transformedVertices.m[r][1].toPerspective(perspectiveDistance);
        auto pNextFront = transformedVertices.m[(r+1)%transformedVertices.rows][0].toPerspective(perspectiveDistance);
        auto pNextBack = transformedVertices.m[(r+1)%transformedVertices.rows][1].toPerspective(perspectiveDistance);
        CV::line(pFront, pBack);

        CV::line(pFront, pNextFront);
        CV::line(pBack, pNextBack);
    }
    int divisions = wireframeDivisions; // Just in case we need to change this later
    int jumpIncr = divisions <= crankVertices.rows ? crankVertices.rows / divisions : 1;
    int halfSize = crankVertices.rows / 2;
    for (int i = 0; i < divisions; i++) {
        int indexA = i * jumpIncr;
        int indexB = i * jumpIncr + halfSize;

        CV::line(
                transformedVertices.m[indexA%crankVertices.rows][0].toPerspective(perspectiveDistance),
                transformedVertices.m[indexB%crankVertices.rows][0].toPerspective(perspectiveDistance)
        );
        CV::line(
                transformedVertices.m[indexA%crankVertices.rows][1].toPerspective(perspectiveDistance),
                transformedVertices.m[indexB%crankVertices.rows][1].toPerspective(perspectiveDistance)
        );
    }
}

void Crank::generateCrankPinVerticesMatrix() {
    int divisions = 10;
    // Each row ([r][0]) is the location of the circle
    crankPinVertices = Matrix<fvec3>(divisions, 1);
    for (int i = 0; i < crankPinVertices.rows; i++) {
        crankPinVertices[i][0] = center + fvec3{radius, 0, i * (depth / divisions)};;
    }
}

void Crank::drawCrankPin() {
//    CV::color(31, 255, 72);
    CV::color(173, 173, 173);

    Matrix<fvec3> transformedVertices(crankPinVertices.rows, crankPinVertices.cols);

    auto transfMatrix = getPinTransformationMatrix();

    for (int i = 0; i < crankPinVertices.rows; i++) {
        for (int j = 0; j < crankPinVertices.cols; j++) {
            auto transformedVertex = transfMatrix * crankPinVertices[i][j].toVector4(1);
            transformedVertices[i][j] = transformedVertex.toVector3();
        }
    }

    for (int i = 0; i < transformedVertices.rows; i++) {
        CV::circle(transformedVertices[i][0].toPerspective(perspectiveDistance), crankPinRadius, 50);
    }
}

/**
 * Returns the transformed center of the crank pin
 */
fvec3 Crank::getTransformedPinCenter() {
    auto transformationMatrix = getPinTransformationMatrix();
    auto transformedCenter = transformationMatrix * (center + fvec3{radius, 0, 0}).toVector4(1);
    return transformedCenter.toVector3();
}

Matrix<float> Crank::getPinTransformationMatrix() {
    auto translateOrigin = Matrix<float>::translate(center * -1);
    auto rotateZ = Matrix<float>::rotateZ(rollAngle);
    auto translateCenter = Matrix<float>::translate(center);

    return translateCenter * rotateZ * translateOrigin;
}

void Crank::setPerspectiveDistance(float distance) {
    perspectiveDistance = distance;
}


