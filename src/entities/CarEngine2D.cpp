//
// Created by daniel on 10/07/23.
//

#include "CarEngine2D.h"
#include "../gl_canvas2d.h"

CarEngine2D::CarEngine2D(int speedRPM) : speedRPM(speedRPM) {
    angle = 0;
    setRPM(speedRPM);
}

void CarEngine2D::setRPM(int rpm) {
    angularVelocity = PI_2 * rpm / 60;
}

void CarEngine2D::keyboardDown(int key) {

}

void CarEngine2D::keyboardUp(int key) {

}

void CarEngine2D::render(float screenWidth, float screenHeight, float dt) {
    /**
     * We could add a lot of methods for drawing each little piece
     * but I don't think that is necessary here since we would just
     * make things harder and NOT easier to understand.
     */

    angle += angularVelocity * dt;

    // Crank & Crankpin
    float crankWidth = 10;
    fvec2 crankPos = {screenWidth / 2, 200};
    float crankRadius = 50;
    float crankMinorRadius = 10;
    CV::color(173, 173, 173);
    CV::circle(crankPos, crankMinorRadius, 50, angle);
    CV::circle(crankPos, crankRadius, 15, angle);
    CV::circle(crankPos, crankRadius - crankWidth/2, 15, angle);
    CV::circle(crankPos, crankRadius + crankWidth/2, 15, angle);
    // Crankpin
    float crankPinRadius = 10;
    fvec2 crankPinPos = {
            crankPos.x + crankRadius * cos(angle),
            crankPos.y + crankRadius * sin(angle)
    };
    CV::color(102, 102, 102);
    CV::circleFill(crankPinPos, crankPinRadius, 50);

    // Connecting Rod & Piston
    float rodHeight = 250.0;
    fvec2 baseY = {0, 1};
    fvec2 radiusVect = { cos(angle), sin(angle) };
    float angleCrankPiston = baseY.angle(radiusVect);
    float pistonRadius = 30;
    float pistonSide = 2.0 * pistonRadius / sqrt(2);
    float halfPistonSide = pistonSide / 2.0;
    fvec2 pistonPos = { crankPos.x, crankPos.y + crankRadius * cos(angleCrankPiston) + sqrt(rodHeight*rodHeight - crankRadius*crankRadius * sin(angleCrankPiston) * sin(angleCrankPiston))};
    // Piston
    CV::color(102, 102, 102);
    CV::circle(pistonPos, pistonRadius, 4, PI/4);
    CV::circleFill(pistonPos, 5, 50, PI/4);

    // Connecting Rod
    CV::color(88, 90, 94);
    CV::line(crankPinPos, pistonPos);
    float rodWidth = 7;
    float rodHalfWidth = rodWidth/2;
    fvec2 rodVertices[] = {
            fvec2{crankPinPos.x - rodHalfWidth, crankPinPos.y},
            fvec2{crankPinPos.x + rodHalfWidth, crankPinPos.y},
            fvec2{pistonPos.x + rodHalfWidth, pistonPos.y},
            fvec2{pistonPos.x - rodHalfWidth, pistonPos.y},
    };
    CV::polygon(rodVertices, 4);

    // Cylinder
    float compressionGapHeight = 20;
    fvec2 cylinderCenter = { crankPos.x, crankPos.y + rodHeight};
    fvec2 cylinderVertices[] = {
            fvec2{cylinderCenter.x - halfPistonSide, cylinderCenter.y - crankRadius - halfPistonSide}, // Left-bottom
            fvec2{cylinderCenter.x + halfPistonSide, cylinderCenter.y - crankRadius - halfPistonSide}, // Right-bottom
            fvec2{cylinderCenter.x + halfPistonSide, cylinderCenter.y + crankRadius + halfPistonSide + compressionGapHeight}, // Right-top
            fvec2{cylinderCenter.x - halfPistonSide, cylinderCenter.y + crankRadius + halfPistonSide + compressionGapHeight}, // Left-top
    };
    CV::color(82, 62, 62);
    CV::polygon(cylinderVertices, 4);
}
