/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         05/2020
//
//  Pode ser utilizada para fazer desenhos, animacoes, e jogos simples.
//  Tem tratamento de mouse e teclado
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp
//
//  Versao 2.0
//
//  Instru��es:
//	  Para alterar a animacao, digite numeros entre 1 e 3
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>

#include "gl_canvas2d.h"
#include "SceneManager.h"

int screenHeight = 700;
int screenWidth = 900;
SceneManager* sceneManager = new SceneManager();
auto previousTime = std::chrono::high_resolution_clock::now();

void render()
{
    auto now = std::chrono::high_resolution_clock::now();

    auto elapsed = std::chrono::duration<float>(now - previousTime).count();
    previousTime = now;
    sceneManager->render(static_cast<float>(screenWidth), static_cast<float>(screenHeight), elapsed);
}

//funcao chamada toda vez que uma tecla for pressionada.
void keyboard(int key) {
    sceneManager->keyboardDown(key);
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key) {
    sceneManager->keyboardUp(key);
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y) {
}

int main(void)
{
    CV::init(&screenWidth, &screenHeight, "Car Engine");
    CV::run();
}
