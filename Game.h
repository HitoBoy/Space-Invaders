#ifndef Game_h
#define Game_h

#include "Base.h"
#include "Boost.h"
#include "Boss.h"
#include "Saucer.h"
#include "Default.h"
#include "Spaceship.h"
#include "Text.h"


class game {
public:
    game();
    ~game();

    void init(std::string title);
    void handle_event();
    void handle_boss();
    void handle_saucer();
    void handle_game();
    void clean();
    void menu(const std::string& item);
    void reset_game();
    bool get_running() { return isRunning; }
    bool check_collision(const SDL_Rect& object1, const SDL_Rect& object2);
    bool check_mouse_vs_item(const int& x, const int& y, const SDL_Rect& rect);
private:
    bool isRunning;
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
    SDL_Event gEvent;
    Mix_Chunk* g_sound_bullet[3];
    Mix_Chunk* g_sound_exp[3];
    Mix_Chunk* g_sound_saucer_hit[2];
    Mix_Chunk* g_sound_boss_hit[2];
    Mix_Chunk* g_sound_level_up;
    Mix_Music* g_music_start;
    TTF_Font* g_font_text;
    TTF_Font* g_font_menu;
    TTF_Font* g_font_end_game;

    base background;
    spaceship SpaceShip;
    Explosion exp;
    Explosion exp_boss;
    Boost boost;
    Text kill_text;
    base support;
    Text heart_text;
    Text lighting_text;
    Text hint;
    Text end_game;
    Boss boss;
    int bullet_level;
    int kill;
    float scrolling;
    int time_end_game;
    int count_num_exp;
    int menu_number;
    std::vector<Saucer*> p_saucer_list;

};







#endif // !Game.h

