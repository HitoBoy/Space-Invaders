#include "game.h"

// màn hình window khi khởi động trò chơi
int main(int argc, char* argv[]) {
    game Game;
    Game.init("Space_Invaders");
    Game.menu("Start");
    while (Game.get_running()) {
        Game.handle_event();
        Game.handle_game();
    }
    Game.clean();
    return 0;
}