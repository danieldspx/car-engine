//
// Created by daniel on 14/04/23.
//

#include "SceneManager.h"
#include "gl_canvas2d.h"
#include "base/Utils.h"
#include "entities/engine/2d/CarEngine2D.h"

SceneManager::SceneManager(float screenWidth, float screenHeight) {
    int rpm = 10;
    carEngine2D = new CarEngine2D(fvec2{screenWidth - 200, 200}, rpm);
    carEngine3D = new CarEngine3D(fvec3{300, 200, 200}, rpm);
}

void SceneManager::render(float screenWidth, float screenHeight, float dt) {
    CV::clear(1,1,1);

    carEngine2D->render(screenWidth, screenHeight, dt);
    carEngine3D->render(screenWidth, screenHeight, dt);
}

void SceneManager::keyboardDown(int key) {
    printf("\nKey Down: %d" , key);
}

void SceneManager::keyboardUp(int key) {
    printf("\nKey Up: %d" , key);
}
