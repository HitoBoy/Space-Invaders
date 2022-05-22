#include "Game.h"


game::game() {
    isRunning = true;
    bullet_level = 0;
    kill = 0;
    scrolling = -(BACKGROUND_HEIGHT - SCREEN_HEIGHT);
    time_end_game = 0;
    count_num_exp = 0;
    menu_number = 0;
}

game::~game(){

}

void game::init(std::string title) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        isRunning = false;
    }
    else {
        gWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            isRunning = false;
        }
        else {
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL) {
                isRunning = false;
            }
            else {
                SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    isRunning = false;
                }
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                    isRunning = false;
                }
                g_sound_bullet[0] = Mix_LoadWAV("sound//blaster.wav");
                g_sound_bullet[1] = Mix_LoadWAV("sound//neutron.wav");
                g_sound_bullet[2] = Mix_LoadWAV("sound//boron.wav");
                g_sound_exp[0] = Mix_LoadWAV("sound//exp.wav");
                g_sound_exp[1] = Mix_LoadWAV("sound//exp_uco.wav");
                g_sound_saucer_hit[0] = Mix_LoadWAV("sound//saucer1.wav");
                g_sound_saucer_hit[1] = Mix_LoadWAV("sound//saucer2.wav");
                g_sound_boss_hit[0] = Mix_LoadWAV("sound//BossHit1.wav");
                g_sound_boss_hit[1] = Mix_LoadWAV("sound//BossHit2.wav");
                g_sound_level_up = Mix_LoadWAV("sound//level_up.wav");
                g_music_start = Mix_LoadMUS("sound//start.mp3");

                if (g_sound_bullet[0] == NULL
                    || g_sound_bullet[1] == NULL
                    || g_sound_bullet[2] == NULL
                    || g_sound_exp[0] == NULL
                    || g_sound_exp[1] == NULL
                    || g_sound_saucer_hit[0] == NULL
                    || g_sound_saucer_hit[1] == NULL
                    || g_sound_boss_hit[0] == NULL
                    || g_sound_boss_hit[1] == NULL
                    || g_sound_level_up == NULL
                    || g_music_start == NULL) {
                    isRunning = false;
                }
                if (TTF_Init() < 0) {
                    isRunning = false;
                }
                g_font_text = TTF_OpenFont("font//font1.ttf", 24);
                g_font_menu = TTF_OpenFont("font//font1.ttf", 50);
                g_font_end_game = TTF_OpenFont("font//font1.ttf", 100);
                if (g_font_text == NULL || g_font_menu == NULL || g_font_end_game == NULL) {
                    isRunning = false;
                }
            }
        }
    }

    //khởi tạo nền và tàu mà mình điều khiển
    background.loadImage("image//background.png", gRenderer);
    SpaceShip.loadImage("image//spacecraft.png", gRenderer);

    //khởi tạo con boss
    boss.loadImage("image//boss.png", gRenderer);
    boss.set_clip();
    boss.SetRect(-WIDTH_BOSS, -HEIGHT_BOSS);
    boss.set_y_val(BOSS_SPEED);
    boss.set_x_val(BOSS_SPEED*3);
    boss.set_heart(BOSS_HEART);
    bullet* p_bullet = new bullet();
    boss.InitBullet(p_bullet, gRenderer);

    //khởi tạo kẻ địch ufo
    int t = 0;
    int y_row = 0;
    for (int c = 0; c < NUMBER_OF_SAUCER; c++) {
        Saucer* p_saucer = new Saucer();
        if (p_saucer) {
            p_saucer->loadImage("image//saucer.png", gRenderer);
            p_saucer->set_clip();
            if (t % NUMBER_OF_SAUCERS_PER_ROW == 0) {
                y_row -= DISTANCE_BETWEEN_SAUCERS;
                t = 0;
            }
            p_saucer->SetRect(10 + t * DISTANCE_BETWEEN_SAUCERS, y_row);
            p_saucer->set_y_val(SAUCER_SPEED);
            p_saucer->set_x_val(SAUCER_SPEED);
            p_saucer->set_heart(SAUCER_HEART);
            int random = rand() % 10;
            if (random < 3) {
                bullet* p_bullet = new bullet();
                p_saucer->InitBullet(p_bullet, gRenderer);
            }
            p_saucer_list.push_back(p_saucer);
            t++;
        }
    }

    //khởi tạo hiệu ứng nổ
    exp.loadImage("image//exp.png", gRenderer);
    exp.set_clip();
    exp_boss.loadImage("image//exp.png", gRenderer);
    exp_boss.set_clip();
    boost.set_clip();

    //khởi tạo biểu tượng số trái tim, số lần nâng cấp, loại súng, kết thúc
    support.loadImage("image//support.png", gRenderer);
    support.SetRect(-20, 10);
    kill_text.SetColor(Text::WHITE);
    heart_text.SetColor(Text::WHITE);
    lighting_text.SetColor(Text::WHITE);
    hint.SetColor(Text::WHITE);
    end_game.SetColor(Text::WHITE);

    isRunning = true;
}

bool game::check_collision(const SDL_Rect& object1, const SDL_Rect& object2) {
    int left_a = object1.x;
    int right_a = object1.x + object1.w;
    int top_a = object1.y;
    int bottom_a = object1.y + object1.h;

    int left_b = object2.x;
    int right_b = object2.x + object2.w;
    int top_b = object2.y;
    int bottom_b = object2.y + object2.h;

    if (left_a > right_b || right_a < left_b || top_a > bottom_b || bottom_a < top_b) {
        return false;
    }
    return true;
}

bool game::check_mouse_vs_item(const int& x, const int& y, const SDL_Rect& rect) {
    if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h) {
        return true;
    }
    return false;
}
// menu khi khởi động trò chơi
void game::menu(const std::string& item) {
    base menu;
    if (!menu.loadImage("image//menu.png", gRenderer)) {
        isRunning = false;
        return;
    }

    const int number_of_item = 3;
    SDL_Rect pos_arr[number_of_item];
    Text text_menu[number_of_item];

    text_menu[0].SetText(item);
    text_menu[0].SetColor(Text::YELLOW);
    text_menu[0].loadText_showText(g_font_menu, gRenderer);
    pos_arr[0].x = SCREEN_WIDTH / 2 - text_menu[0].GetRect().w / 2;
    pos_arr[0].y = SCREEN_HEIGHT - 200;
    text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);

    text_menu[1].SetText("Quit");
    text_menu[1].SetColor(Text::YELLOW);
    text_menu[1].loadText_showText(g_font_menu, gRenderer);
    pos_arr[1].x = SCREEN_WIDTH / 2 - text_menu[1].GetRect().w / 2;
    pos_arr[1].y = SCREEN_HEIGHT - 100;
    text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);

    text_menu[2].SetText("Back");
    text_menu[2].SetColor(Text::YELLOW);
    text_menu[2].loadText_showText(g_font_menu, gRenderer);
    pos_arr[2].x = 10;
    pos_arr[2].y = 10;
    text_menu[2].SetRect(pos_arr[3].x, pos_arr[3].y);

    int xm = 0;
    int ym = 0;
    Mix_PlayMusic(g_music_start, -1);
    bool quit = true;
    while (quit) {
        if (menu_number == 0) {
            menu.Render(gRenderer);
            for (int i = 0; i < number_of_item - 1; i++) {
                text_menu[i].loadText_showText(g_font_menu, gRenderer);
            }
        }
        while (SDL_PollEvent(&gEvent) != 0) {
            SpaceShip.Control(gEvent, gRenderer, g_sound_bullet, bullet_level, g_sound_level_up);
            if (gEvent.type == SDL_QUIT) {
                isRunning = false;
                quit = false;
            }
            else if (gEvent.type == SDL_MOUSEMOTION) {
                xm = gEvent.motion.x;
                ym = gEvent.motion.y;

                for (int i = 0; i < number_of_item; i++) {
                    if (check_mouse_vs_item(xm, ym, text_menu[i].GetRect())) { text_menu[i].SetColor(Text::WHITE); }
                    else { text_menu[i].SetColor(Text::YELLOW); }
                }
            }
            if (gEvent.type == SDL_MOUSEBUTTONDOWN) {
                xm = gEvent.button.x;
                ym = gEvent.button.y;

                for (int i = 0; i < number_of_item; i++) {
                    if (menu_number == 0) {
                        if (check_mouse_vs_item(xm, ym, text_menu[i].GetRect())) {
                            if (i == 0) { isRunning = true; quit = false; }
                            else if (i == 1) { isRunning = false; quit = false; }
                            Mix_PlayChannel(-1, g_sound_level_up, 0);
                        }
                    }
                }
            }
        }
        SDL_RenderPresent(gRenderer);
    }
    Mix_PauseMusic();
}
// tạo màn mới
void game::reset_game() {
    bullet_level = 0;
    kill = 0;
    count_num_exp = 0;
    scrolling = -(BACKGROUND_HEIGHT - SCREEN_HEIGHT);
    time_end_game = 0;
    SpaceShip.set_bullet_type(TYPE1);
    SpaceShip.SetRect(SCREEN_WIDTH / 2, SCREEN_HEIGHT - HEIGHT_PLAYER);
    SpaceShip.set_status(true);
    SpaceShip.set_heart(SAUCER_HEART);
    boss.SetRect(-WIDTH_BOSS, -HEIGHT_BOSS);
    boss.set_heart(BOSS_HEART);
    for (int i = 0; i < boss.get_bullet_list().size(); i++) {
        bullet* p_bullet = boss.get_bullet_list().at(i);
        if (p_bullet) {
            p_bullet->SetRect(boss.GetRect().x + WIDTH_BOSS / 2, boss.GetRect().y + HEIGHT_BOSS);
        }
    }
    int t = 0;
    int y_row = -DISTANCE_BETWEEN_SAUCERS;
    for (int c = 0; c < NUMBER_OF_SAUCER; c++) {
        Saucer* p_saucer = p_saucer_list.at(c);
        if (t % NUMBER_OF_SAUCERS_PER_ROW == 0) {
            y_row -= DISTANCE_BETWEEN_SAUCERS;
            t = 0;
        }
        p_saucer->set_come_back(true);
        p_saucer->SetRect(10 + t * DISTANCE_BETWEEN_SAUCERS, y_row);
        p_saucer->set_heart(SAUCER_HEART);
        p_saucer->set_status_right();
        t++;
        for (int i = 0; i < p_saucer->get_bullet_list().size(); i++) {
            bullet* p_bullet = p_saucer->get_bullet_list().at(i);
            if (p_bullet) {
                p_bullet->SetRect(p_saucer->GetRect().x + WIDTH_SAUCER / 2 - p_bullet->GetRect().w / 2, p_saucer->GetRect().y + HEIGHT_SAUCER);
            }
        }
    }
}
void game::handle_event() {
    while (SDL_PollEvent(&gEvent)) {
        if (gEvent.type == SDL_QUIT) {
            isRunning = false;
        }
        SpaceShip.Control(gEvent, gRenderer, g_sound_bullet, bullet_level, g_sound_level_up);
    }
}
//thiết lập boss
void game::handle_boss() {
    if (kill >= NUMBER_OF_SAUCER && boss.get_heart() >= 0) {
        boss.show_heart_boss(gRenderer, 420, 20, boss.get_heart()*10, 6);

        boss.Move();
        boss.Show(gRenderer);
        boss.MakeBullet(gRenderer);

        //đạn từ con boss lên tàu
        bool Col1 = false;
        std::vector<bullet*> boss_bullet_list = boss.get_bullet_list();
        for (int b = 0; b < boss_bullet_list.size(); b++) {
            bullet* p_bullet = boss_bullet_list.at(b);
            if (p_bullet) {
                Col1 = check_collision(p_bullet->GetRect(), SpaceShip.GetRect());
            }
        }
        //va chạm của tàu với boss
        bool Col2 = check_collision(SpaceShip.GetRect(), boss.GetRectFrame());
        if (Col1 || Col2) {
            Mix_PlayChannel(-1, g_sound_exp[0], 0);

            //nổ khi va chạm
            int x_pos = (SpaceShip.GetRect().x + WIDTH_PLAYER / 2) - WIDTH_FRAME_EXP / 2;
            int y_pos = (SpaceShip.GetRect().y + HEIGHT_PLAYER / 2) - HEIGHT_FRAME_EXP / 2;
            exp.SetRect(x_pos, y_pos);
            exp.set_frame(0);

            SpaceShip.SetRect(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
            SpaceShip.set_status(false);
            SpaceShip.decrease_heart();
            if (SpaceShip.get_heart() >= 0) {
                bullet_level = bullet_level < 2 ? 0 : (bullet_level - 1);
            }
        }
        //va chạm đạn lên boss
        std::vector<bullet*> s_bullet_list = SpaceShip.get_bullet_list();
        for (int sb = 0; sb < s_bullet_list.size(); sb++) {
            bullet* p_bullet = s_bullet_list.at(sb);
            if (p_bullet != NULL) {
                bool Col3 = check_collision(p_bullet->GetRect(), boss.GetRectFrame());
                if (Col3) {
                    boss.Decrease((SpaceShip.get_bullet_damage()) + bullet_level * BULLET_DAMAGE_LEVEL_UP);
                    Mix_PlayChannel(-1, g_sound_boss_hit[0], 0);
                    SpaceShip.RemoveBullet(sb);

                    if (boss.get_heart() < 0) {
                        kill++;
                        int x_pos = (boss.GetRect().x + WIDTH_BOSS / 2) - WIDTH_FRAME_EXP / 2;
                        int y_pos = (boss.GetRect().y + HEIGHT_BOSS / 2) - HEIGHT_FRAME_EXP / 2;
                        exp_boss.SetRect(x_pos, y_pos); // hiệu ứng nổ
                        exp_boss.set_frame(0);
                        boss.SetRect(SCREEN_WIDTH / 2, -SCREEN_HEIGHT);
                        Mix_PlayChannel(-1, g_sound_exp[0], 0);
                    }
                }
            }
        }
    }
}
// tác vụ của ufo
void game::handle_saucer() {
    if (kill < NUMBER_OF_SAUCER * 2) {
        for (int ck = 0; ck < p_saucer_list.size(); ck++) {
            Saucer* p_saucer = p_saucer_list.at(ck);
            if (p_saucer) {
                p_saucer->Move();
                p_saucer->Show(gRenderer);
                p_saucer->HandleBullet(gRenderer);
            }

            // ảnh hưởng của đạn từ ufo lên tàu chiến
            bool Col1 = false;
            std::vector<bullet*> bullet_list = p_saucer->get_bullet_list();
            for (int b = 0; b < bullet_list.size(); b++) {
                bullet* p_bullet = bullet_list.at(b);
                if (p_bullet) {
                    Col1 = check_collision(p_bullet->GetRect(), SpaceShip.GetRect());
                    if (Col1 == true) {
                        p_saucer->RemoveBullet(b);
                        break;
                    }
                }
            }

            //va chạm từ tàu chiến lên ufo
            bool Col2 = check_collision(SpaceShip.GetRect(), p_saucer->GetRectFrame());
            if (Col1 || Col2) {
                Mix_PlayChannel(-1, g_sound_exp[0], 0);

                int x_pos = (SpaceShip.GetRect().x + WIDTH_PLAYER / 2) - WIDTH_FRAME_EXP / 2;
                int y_pos = (SpaceShip.GetRect().y + HEIGHT_PLAYER / 2) - HEIGHT_FRAME_EXP / 2;
                exp.SetRect(x_pos, y_pos); // hiệu ứng nổ
                exp.set_frame(0);

                SpaceShip.SetRect(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
                SpaceShip.set_status(false);
                SpaceShip.decrease_heart();
                if (SpaceShip.get_heart() >= 0) {
                    bullet_level = bullet_level < 2 ? 0 : (bullet_level - 1);
                }
            }


            //đạn từ tàu chiến lên ufo
            std::vector<bullet*> s_bullet_list = SpaceShip.get_bullet_list();
            for (int sb = 0; sb < s_bullet_list.size(); sb++) {
                bullet* p_bullet = s_bullet_list.at(sb);
                if (p_bullet != NULL) {
                    bool Col3 = check_collision(p_bullet->GetRect(), p_saucer->GetRectFrame());
                    if (Col3) {
                        p_saucer->Decrease((SpaceShip.get_bullet_damage()) + bullet_level * BULLET_DAMAGE_LEVEL_UP);
                        Mix_PlayChannel(-1, g_sound_saucer_hit[0], 0);
                        SpaceShip.RemoveBullet(sb);

                        if (p_saucer->get_heart() <= 0) {
                            p_saucer->set_heart(SAUCER_HEART);
                            kill++;
                            Mix_PlayChannel(-1, g_sound_saucer_hit[1], 0);

                            p_saucer->SetRect(p_saucer->GetRect().x, -3 * SCREEN_HEIGHT);
                            if (kill > NUMBER_OF_SAUCER) {
                                p_saucer->set_come_back(false);
                            }

                            if (kill % ONE_TURN_BOOST == 0) {
                                boost.set_boost_type(boost.random_boost());
                                boost.LoadImageBoost(gRenderer);
                                boost.set_y_val(BOOST_SPEED);
                                boost.SetRect((rand() % (SCREEN_WIDTH - 2 * BOOST_WIDTH) + BOOST_WIDTH), -BOOST_HEIGHT);
                                boost.set_come_back(true);
                            }
                        }
                    }
                }
            }
        }
    }
}

//tác vụ của trò chơi
void game::handle_game() {
    SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
    SDL_RenderClear(gRenderer);

    // hình nền
    scrolling += SCREEN_SPEED;
    if (scrolling < 0) {
        background.Render(gRenderer);
        background.SetRect(0, scrolling);
    }
    else {
        background.Render(gRenderer);
        background.SetRect(0, 0);
    }

    // tàu chiến
    SpaceShip.Move();
    SpaceShip.Show(gRenderer);
    SpaceShip.HandleBullet(gRenderer);

    //kẻ địch
    handle_saucer();
    handle_boss();

    //hiệu ứng nổ
    if (exp.get_frame() < NUMBER_OF_FRAME * 2) {
        exp.Show(gRenderer);
    }
    if (exp_boss.get_frame() < NUMBER_OF_FRAME * 2) {
        exp_boss.Show(gRenderer);
        if (exp_boss.get_frame() >= NUMBER_OF_FRAME * 2 && count_num_exp < NUMBER_OF_EXP) {
            Mix_PlayChannel(-1, g_sound_exp[0], 0);
            exp_boss.set_frame(0);
            count_num_exp++;
        }
    }

    // Hiệu ứng thua cuộc
    if (SpaceShip.get_heart() == 0) {
        if (time_end_game < 300) {
            time_end_game++;
            end_game.SetText("Game Over");
            end_game.SetRect(310, SCREEN_HEIGHT / 5);
            end_game.loadText_showText(g_font_end_game, gRenderer);
        }
        else {
            menu("Play Again?");
            reset_game();
        }
    }
    else {
        if (SpaceShip.get_status() == false) {
            hint.SetText("Press 'ENTER' to revive");
            hint.SetRect(280, SCREEN_HEIGHT / 4);
            hint.loadText_showText(g_font_menu, gRenderer);
        }
    }
    // Hiệu ứng chiến thắng
    if (boss.get_heart() <= 0) {
        if (time_end_game < 300) {
            time_end_game++;
            end_game.SetText("Victorious!");
            end_game.SetRect(310, SCREEN_HEIGHT / 5);
            end_game.loadText_showText(g_font_end_game, gRenderer);
        }
        else {
            menu("Play Again");
            reset_game();
        }
    }

    // Nâng cấp
    boost.Move(SCREEN_WIDTH, SCREEN_HEIGHT);
    boost.Show(gRenderer);

    bool Col4 = check_collision(SpaceShip.GetRect(), boost.get_boost_type() < LEVEL_UP ? boost.GetRect() : boost.GetRectFrame());
    if (Col4) {
        boost.SetRect(-BOOST_WIDTH, -BOOST_HEIGHT);
        if (bullet_level < 3 && ((boost.get_boost_type() == SpaceShip.get_bullet_type()) || boost.get_boost_type() == LEVEL_UP)) {
            bullet_level++;
        }
        Mix_PlayChannel(-1, g_sound_level_up, 0);
        if (boost.get_boost_type() < LEVEL_UP) {
            SpaceShip.set_bullet_type(boost.get_boost_type());
        }

        boost.set_come_back(false);
    }

    // Số máu, số quái bị hạ gục và số nâng cấp
    support.Render(gRenderer);
    heart_text.SetText(std::to_string(SpaceShip.get_heart()));
    heart_text.SetRect(195, 15);
    heart_text.loadText_showText(g_font_text, gRenderer);
    kill_text.SetText(std::to_string(kill));
    kill_text.SetRect(50, 15);
    kill_text.loadText_showText(g_font_text, gRenderer);
    lighting_text.SetText(std::to_string(bullet_level));
    lighting_text.SetRect(280, 15);
    lighting_text.loadText_showText(g_font_text, gRenderer);


    SDL_RenderPresent(gRenderer);
}
//thoát game
void game::clean() {
    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);
    gWindow = NULL;
    gRenderer = NULL;

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
}