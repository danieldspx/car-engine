//
// Created by daniel on 10/07/23.
//

#include "Crank.h"
#include "../../../../gl_canvas2d.h"

/**
 * Radius is in the xy plane and depth is the z component to add when generating the vertices
 */
Crank::Crank(fvec3 center, int speedRPM, float perspectiveDistance, float radius, float depth): center(center), speedRPM(speedRPM), radius(radius), depth(depth), perspectiveDistance(perspectiveDistance) {
    setRPM(speedRPM);
    generateVerticesMatrix();
}

void Crank::render(float screenWidth, float screenHeight, float dt) {
    rollAngle += angularVelocity * dt;
    drawCrank();
}

void Crank::setRPM(int rpm) {
    angularVelocity = PI_2 * rpm / 60;
}

void Crank::generateVerticesMatrix() {
    int divisions = 40;
    crankVertices = Matrix<fvec3>(divisions, 2);
    std::cout << "Crank Position: ";
    center.print();
    float incr = PI_2/divisions;
    float ang = 0;
    for (int i = 0; i < divisions; i++) {
        crankVertices.m[i][0] = fvec3{ center.x + radius * cos(ang), center.y + radius * sin(ang), center.z };
        crankVertices.m[i][1] = fvec3{ center.x + radius * cos(ang), center.y + radius * sin(ang), center.z + depth };
        ang += incr;
    }
    crankVertices.printMatrix();
}

void Crank::drawCrank() {
    CV::color(173, 173, 173);
    for (int r = 0; r < crankVertices.rows; r++) {
        auto pFront = crankVertices.m[r][0].toPerspective(perspectiveDistance);
        auto pBack = crankVertices.m[r][1].toPerspective(perspectiveDistance);
        auto pNextFront = crankVertices.m[(r+1)%crankVertices.rows][0].toPerspective(perspectiveDistance);
        auto pNextBack = crankVertices.m[(r+1)%crankVertices.rows][1].toPerspective(perspectiveDistance);
        CV::line(pFront, pBack);

        CV::line(pFront, pNextFront);
        CV::line(pBack, pNextBack);
    }
    int divisions = 8;
    int jumpIncr = crankVertices.rows / divisions;
    for (int i = 1; i < divisions; i++) {
        int indexA = i * jumpIncr;
        int indexB = crankVertices.rows - i * jumpIncr;

        if (indexA < crankVertices.rows && indexB < crankVertices.rows) {
            CV::line(
                    crankVertices.m[indexA%crankVertices.rows][0].toPerspective(perspectiveDistance),
                    crankVertices.m[indexB%crankVertices.rows][0].toPerspective(perspectiveDistance)
            );
            CV::line(
                    crankVertices.m[indexA%crankVertices.rows][1].toPerspective(perspectiveDistance),
                    crankVertices.m[indexB%crankVertices.rows][1].toPerspective(perspectiveDistance)
            );
        }
    }
}

void Crank::setPerspectiveDistance(float distance) {
    perspectiveDistance = distance;
}


