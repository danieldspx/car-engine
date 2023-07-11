//
// Created by daniel on 14/04/23.
//

#include "SceneManager.h"
#include "gl_canvas2d.h"
#include "base/Utils.h"
#include "entities/CarEngine2D.h"

SceneManager::SceneManager() {
    carEngine2D = new CarEngine2D(80);
}

float angle = 0;
void SceneManager::render(float screenWidth, float screenHeight, float dt) {
    CV::clear(1,1,1);

    carEngine2D->render(screenWidth, screenHeight, dt);
}

void SceneManager::keyboardDown(int key) {
    printf("\nKey Down: %d" , key);
}

void SceneManager::keyboardUp(int key) {
    printf("\nKey Up: %d" , key);
}
