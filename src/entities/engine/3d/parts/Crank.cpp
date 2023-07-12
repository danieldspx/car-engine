//
// Created by daniel on 10/07/23.
//

#include "Crank.h"
#include "../../../../gl_canvas2d.h"

/**
 * Radius is in the xy plane and depth is the z component to add when generating the vertices
 */
Crank::Crank(fvec3 center, int speedRPM, float perspectiveDistance, float radius, float depth): center(center), speedRPM(speedRPM), radius(radius), depth(depth), perspectiveDistance(perspectiveDistance) {
    rollAngle = pitchAngle = yawAngle = 0;
    wireframeDivisions = 30;
    crankPinRadius = 30;
    crankPinDivisions = 12;
    setRPM(speedRPM);
    generateCrankVerticesMatrix();
    generateCrankPinVerticesMatrix();
}

void Crank::render(float screenWidth, float screenHeight, float dt) {
    if (rotateY) yawAngle += 2 * dt;
    if (rotateX) pitchAngle += 2 * dt;
    if (rotateZ) rollAngle += angularVelocity * dt;

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
    auto matrixRotateZ = Matrix<float>::rotateZ(rollAngle);
    auto matrixRotateX = Matrix<float>::rotateX(pitchAngle);
    auto matrixRotateY = Matrix<float>::rotateY(yawAngle);
    auto translateCenter = Matrix<float>::translate(center);

    auto transfMatrix = translateCenter  * matrixRotateZ * matrixRotateY * matrixRotateX * translateOrigin;

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
    // Each row is the depth of the circle and the columns are the points of the circle
    crankPinVertices = Matrix<fvec3>(crankPinDivisions, crankPinDivisions);
    float angIcr = PI_2 / crankPinDivisions;
    float depthIcr = depth / crankPinDivisions;
    for (int row = 0; row < crankPinVertices.rows; row++) {
        float angAcc = 0;
        for (int i = 0; i < crankPinVertices.cols; i++) {
            crankPinVertices[row][i] =  fvec3{
                center.x + radius + crankPinRadius * cos(angAcc),
                center.y + crankPinRadius * sin(angAcc),
                center.z + row * depthIcr
            };
            angAcc += angIcr;
        }
    }
}

void Crank::drawCrankPin() {
    CV::color(173, 173, 173);

    // Transform Crank Pin
    Matrix<fvec3> transformedVertices(crankPinVertices.rows, crankPinVertices.cols);
    auto transfMatrix = getPinTransformationMatrix();
    for (int i = 0; i < crankPinVertices.rows; i++) {
        for (int j = 0; j < crankPinVertices.cols; j++) {
            auto transformedVertex = transfMatrix * crankPinVertices[i][j].toVector4(1);
            transformedVertices[i][j] = transformedVertex.toVector3();
        }
    }

    // Draw circles
    for (int row = 0; row < transformedVertices.rows; row++) {
        for (int i = 0; i < transformedVertices.cols; i++) {
            auto currentVertex = transformedVertices[row][i];
            auto nextVertexOnLine = transformedVertices[row][(i + 1) % transformedVertices.cols];

            CV::line(currentVertex.toPerspective(perspectiveDistance), nextVertexOnLine.toPerspective(perspectiveDistance));
        }
    }

    // Draw a line from the front to the back on each point
    for (int i = 0; i < transformedVertices.cols; i++) {
        auto bottomVertex = transformedVertices[0][i];
        auto topVertex = transformedVertices[transformedVertices.cols - 1][i];

        CV::line(bottomVertex.toPerspective(perspectiveDistance), topVertex.toPerspective(perspectiveDistance));
    }

    int divisions = crankPinDivisions;
    int jumpIncr = divisions <= crankPinVertices.cols ? crankPinVertices.cols / divisions : 1;
    int halfSize = crankPinVertices.cols / 2;
    for (int i = 0; i < divisions; i++) {
        int indexA = i * jumpIncr;
        int indexB = i * jumpIncr + halfSize;

        CV::line(
                transformedVertices[0][indexA%crankPinVertices.cols].toPerspective(perspectiveDistance),
                transformedVertices[0][indexB%crankPinVertices.cols].toPerspective(perspectiveDistance)
        );
        auto lastIndex = transformedVertices.rows - 1;
        CV::line(
                transformedVertices[lastIndex][indexA%crankPinVertices.cols].toPerspective(perspectiveDistance),
                transformedVertices[lastIndex][indexB%crankPinVertices.cols].toPerspective(perspectiveDistance)
        );
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

fvec2 Crank::crankPinUnitVector() {
    return fvec2 {cos(rollAngle), sin(rollAngle)};
}

Matrix<float> Crank::getPinTransformationMatrix() {
    auto translateOrigin = Matrix<float>::translate(center * -1);
    auto matrixRotateZ = Matrix<float>::rotateZ(rollAngle);
    auto matrixRotateX = Matrix<float>::rotateX(pitchAngle);
    auto matrixRotateY = Matrix<float>::rotateY(yawAngle);
    auto translateCenter = Matrix<float>::translate(center);

    return translateCenter * matrixRotateZ * matrixRotateY * matrixRotateX  * translateOrigin;
}

void Crank::setPerspectiveDistance(float distance) {
    perspectiveDistance = distance;
}

void Crank::keyboardDown(int key) {

}

void Crank::keyboardUp(int key) {
    if (key == 120 || key == 88) { // X
        rotateX = !rotateX;
        rotateZ = false;
        rotateY = false;
        printf("\nRotating in X: %d\n", rotateX);
    } else if (key == 121 || key == 89) { // Y
        rotateY = !rotateY;
        rotateZ = false;
        rotateX = false;
        printf("\nRotating in Y: %d\n", rotateY);
    } else if (key == 122 || key == 90) { // Z
        rotateZ = !rotateZ;
        rotateY = false;
        rotateX = false;
        printf("\nRotating in Z: %d\n", rotateZ);
    }
}


