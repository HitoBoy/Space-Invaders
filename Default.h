#ifndef Default_h_
#define Default_h_

#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

using namespace std;

const int BACKGROUND_WIDTH = 1200;
const int BACKGROUND_HEIGHT = 3840;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 760;
const float SCREEN_SPEED = 0.4;

const int COLOR_KEY_R = 170;
const int COLOR_KEY_G = 170;
const int COLOR_KEY_B = 170;
const int RENDER_DRAW_COLOR = 255;

const int NUMBER_OF_SAUCER = 20;
const int ONE_TURN_BOOST = 5;
const int NUMBER_OF_EXP = 3;
const int BOSS_HEART = 100;
const int SAUCER_HEART = 4;
const int DISTANCE_BETWEEN_SAUCERS = 200;
const int NUMBER_OF_SAUCERS_PER_ROW = 5;
const float BULLET_DAMAGE_LEVEL_UP = 0.5;
const int TYPE1 = 0;
const int TYPE2 = 1;
const int TYPE3 = 2;
const int LEVEL_UP = 3;
struct StatusSaucer {
    int turn_left;
    int turn_right;
    int turn_up;
    int turn_down;
};

#endif
