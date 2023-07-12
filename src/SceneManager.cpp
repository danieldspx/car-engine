//
// Created by daniel on 14/04/23.
//

#include "SceneManager.h"
#include "gl_canvas2d.h"
#include "base/Utils.h"
#include "entities/engine/2d/CarEngine2D.h"

SceneManager::SceneManager(float screenWidth, float screenHeight) {
    rpm = 10;
    carEngine2D = new CarEngine2D(fvec2{screenWidth - 200, 200}, rpm);
    carEngine3D = new CarEngine3D(fvec3{200, 100, 200}, rpm);
}

void SceneManager::render(float screenWidth, float screenHeight, float dt) {
    CV::clear(1,1,1);

    CV::color(0,0,0);
    CV::text(10, screenHeight - 10, "Pression X, Y ou Z para rotacionar nesses eixos.");
    CV::text(10, screenHeight - 25, "Nota: Se voce esta rotacionando em um eixo X e pressionar Z");
    CV::text(10, screenHeight - 40, "o eixo X para de rotacionar para o Z rotacionar.");
    CV::text(10, screenHeight - 55, "Isso foi feito pra facilitar a visualizacao do motor.");

    CV::text(10, screenHeight - 90, "Pressione A ou S para aumentar ou diminuir o RPM");

    carEngine2D->render(screenWidth, screenHeight, dt);
    carEngine3D->render(screenWidth, screenHeight, dt);
}

void SceneManager::keyboardDown(int key) {
    printf("\nKey Down: %d" , key);
    carEngine3D->keyboardDown(key);
}

void SceneManager::keyboardUp(int key) {
    printf("\nKey Up: %d" , key);
    carEngine3D->keyboardUp(key);
    if (key == 65 || key == 97) { // Letter A
        rpm += 10;
        carEngine2D->setRPM(rpm);
        carEngine3D->setRPM(rpm);
    } else if (key == 83 || key == 115) { // Letter A
        rpm -= 10;
        if (rpm < 10) rpm = 10;
        carEngine2D->setRPM(rpm);
        carEngine3D->setRPM(rpm);
    }
}
