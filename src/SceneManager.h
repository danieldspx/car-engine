//
// Created by daniel on 14/04/23.
//

#ifndef VECTORGRAPHICS_SCENEMANAGER_H
#define VECTORGRAPHICS_SCENEMANAGER_H

#include <random>
#include <map>
#include <vector>
#include <functional>
#include "base/interfaces/IMouse.h"
#include "base/interfaces/IRender.h"
#include "base/interfaces/IKeyboard.h"
#include "entities/CarEngine2D.h"

#define LANE_POINTS 100

class SceneManager: public IRender, public IKeyboard{
private:
    CarEngine2D* carEngine2D;
public:
    SceneManager();

    void render(float screenWidth, float screenHeight, float dt) override;

    void keyboardDown(int key) override;

    void keyboardUp(int key) override;
};


#endif //VECTORGRAPHICS_SCENEMANAGER_H
