
#include <cstdlib>
#include "AcsGameEngine/MainGame.h"

int main(int argc, char** argv) {

    AcsGameEngine::MainGame game;

    game.getWindow()->setTitle("Tic Tac Toe"); 

    game.run();




    //board 2,0, 422, 364
    //circle 448, 4, 114, 110
    //x 448, 131, 114, 110
    return 0;
}

