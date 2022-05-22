#include "Spaceship.h"

spaceship::spaceship() {
    _rect.x = SCREEN_WIDTH / 2;
    _rect.y = SCREEN_HEIGHT - HEIGHT_PLAYER;
    _rect.w = WIDTH_PLAYER;
    _rect.h = HEIGHT_PLAYER;

    x_val = 0;
    y_val = 0;

    bullet_type = TYPE1;
    _status = true;
    bullet_damage = 0;
    _heart = PLAYER_HEART;
}
spaceship::~spaceship() {

}
//di chuyển tàu chiến
void spaceship::Control(SDL_Event event, SDL_Renderer* screen, Mix_Chunk* bullet_sound[4], int bullet_level, Mix_Chunk* g_sound_level_up) {
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
        case SDLK_w:
            y_val -= PLAYER_SPEED;
            break;
        case SDLK_s:
            y_val += PLAYER_SPEED;
            break;
        case SDLK_d:
            x_val += PLAYER_SPEED;
            break;
        case SDLK_a:
            x_val -= PLAYER_SPEED;
            break;
        }
    }
    else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
        case SDLK_w:
            y_val += PLAYER_SPEED;
            break;
        case SDLK_s:
            y_val -= PLAYER_SPEED;
            break;
        case SDLK_d:
            x_val -= PLAYER_SPEED;
            break;
        case SDLK_a:
            x_val += PLAYER_SPEED;
            break;
        }
    }
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        if (event.key.keysym.sym == SDLK_SPACE) {
            if (_status == true) {
                bullet* p_bullet = new bullet();
                p_bullet->set_bullet_type(bullet_type);

                if (bullet_type == TYPE1) {
                    Mix_PlayChannel(-1, bullet_sound[0], 0);
                    p_bullet->set_y_val(-TYPE1_SPEED);
                    bullet_damage = 2;
                }
                else if (bullet_type == TYPE2) {
                    Mix_PlayChannel(-1, bullet_sound[1], 0);
                    p_bullet->set_y_val(-TYPE2_SPEED);
                    bullet_damage = 2.5;
                }
                else if (bullet_type == TYPE3) {
                    Mix_PlayChannel(-1, bullet_sound[2], 0);
                    p_bullet->set_y_val(-TYPE3_SPEED);
                    bullet_damage = 1.5;
                }

                p_bullet->LoadImgBullet(screen, bullet_level);
                p_bullet->SetRect(this->_rect.x + this->_rect.w / 2 - p_bullet->GetRect().w / 2, this->_rect.y - p_bullet->GetRect().h);
                p_bullet->set_is_move(true);
                bullet_list.push_back(p_bullet);
            }
        }
        if (event.key.keysym.sym == SDLK_RETURN) {
            if (_heart > 0) {
                if (_status == false) {
                    Mix_PlayChannel(-1, g_sound_level_up, 0);
                    _status = true;
                    _rect.x = SCREEN_WIDTH / 2;
                    _rect.y = SCREEN_HEIGHT - HEIGHT_PLAYER;
                }
            }
        }
    }
}
void spaceship::Show(SDL_Renderer* screen) {
    if (_status == true) {
        Render(screen);
    }
}
void spaceship::Move() {
    if (_status == true) {
        _rect.x += x_val;
        if (_rect.x < 0 || _rect.x + WIDTH_PLAYER > SCREEN_WIDTH) {
            _rect.x -= x_val;
        }
        _rect.y += y_val;
        if (_rect.y < 0 || _rect.y + HEIGHT_PLAYER > SCREEN_HEIGHT) {
            _rect.y -= y_val;
        }
    }
}
//thi triển đạn
void spaceship::HandleBullet(SDL_Renderer* screen) {
    for (int i = 0; i < bullet_list.size(); i++) {
        bullet* p_bullet = bullet_list.at(i);
        if (p_bullet != NULL) {
            if (p_bullet->get_is_move()) {
                p_bullet->Render(screen);
                p_bullet->HandleMoveSpaceshipBullet();
            }
            else {
                if (p_bullet != NULL) {
                    bullet_list.erase(bullet_list.begin() + i);

                    delete p_bullet;
                    p_bullet = NULL;
                }
            }
        }
    }
}

void spaceship::RemoveBullet(const int& idx) {
    for (int i = 0; i < bullet_list.size(); i++) {
        if (idx < bullet_list.size()) {
            bullet* p_bullet = bullet_list.at(idx);
            bullet_list.erase(bullet_list.begin() + idx);

            if (p_bullet != NULL) {
                delete p_bullet;
                p_bullet = NULL;
            }
        }
    }
}