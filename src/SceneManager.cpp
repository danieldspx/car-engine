//
// Created by daniel on 14/04/23.
//

#include "SceneManager.h"
#include "gl_canvas2d.h"
#include "base/Utils.h"

SceneManager::SceneManager() {}

float angle = 0;
void SceneManager::render(float screenWidth, float screenHeight, float dt) {
    CV::clear(0,0,0);

    // Crank Circle
    CV::color(5);
    fvec2 crankCirclePos = {screenWidth / 2, screenHeight / 2};
    float crankCircleRadius = 10;
    CV::circle(crankCirclePos, crankCircleRadius, 50);

    // Crank-Rods Connection
    CV::color(6);
    angle += 5 * dt;
    fvec2 centerCR = {
            crankCirclePos.x + crankCircleRadius * cos(angle),
            crankCirclePos.y + crankCircleRadius * sin(angle)
    };
    CV::circleFill(centerCR, 3, 50);

//    CV::color(4);
//    float pistonDistance = 40;
//    fvec2 pistonPos = { crankCirclePos.x, crankCirclePos.y + pistonDistance + 2*crankCircleRadius + crankCircleRadius*sin(angle) };
//    CV::circleFill(pistonPos, 3, 50);
//    CV::color(7);
//    CV::line(centerCR, pistonPos);
//    printf("\nDistance: %f", centerCR.distance(pistonPos));

    ////// T2
//    float l2 = 40.0;
//    float cilinderAngle = asin(crankCircleRadius / l2);
//    CV::color(4);
//    fvec2 pistonPos = { crankCirclePos.x, crankCirclePos.y + crankCircleRadius * sin(angle) + l2 * cos(cilinderAngle)};
//    CV::circleFill(pistonPos, 3, 50);
//    CV::color(7);
//    CV::line(centerCR, pistonPos);
//    printf("\nDistance: %f", centerCR.distance(pistonPos));

    ///// T3
    // usar wikipedia
    float l2 = 40.0;
    fvec2 baseY = {0, 1};
    fvec2 radiusVect = { cos(angle), sin(angle) };
    float angleCranckPiston = baseY.angle(radiusVect);
    fvec2 pistonPos = { crankCirclePos.x, crankCirclePos.y + crankCircleRadius * cos(angleCranckPiston) + sqrt(l2*l2 - crankCircleRadius*crankCircleRadius * sin(angleCranckPiston) * sin(angleCranckPiston))};
    CV::circleFill(pistonPos, 3, 50);
    CV::color(7);
    CV::line(centerCR, pistonPos);
    printf("\nDistance: %f", centerCR.distance(pistonPos));
    //    printf("\nAngle: %f", baseY.angle(radiusVect)*180/PI);
}

void SceneManager::keyboardDown(int key) {
    printf("\nKey Down: %d" , key);
}

void SceneManager::keyboardUp(int key) {
    printf("\nKey Up: %d" , key);
}
