#include "Boss.h"

Boss::Boss() {
    _rect.x = SCREEN_WIDTH;
    _rect.y = SCREEN_HEIGHT / 2;
    x_val = 0;
    y_val = 0;
    _status.turn_down = 0;
    _status.turn_up = 0;
    _status.turn_left = 1;
    _status.turn_right = 0;
    _frame = 0;
    _heart = 0;
}
Boss::~Boss() {

}
SDL_Rect Boss::GetRectFrame() {
    SDL_Rect rect;
    rect.x = _rect.x;
    rect.y = _rect.y;
    rect.w = WIDTH_BOSS;
    rect.h = HEIGHT_BOSS;
    return rect;
}
//hình ảnh của boss
void Boss::set_clip() {
    for (int i = 0; i < 9; i++) {
        _clip[i].x = i * WIDTH_BOSS;
        _clip[i].y = 0;
        _clip[i].w = WIDTH_BOSS;
        _clip[i].h = HEIGHT_BOSS;
    }
}
void Boss::Show(SDL_Renderer* screen) {
    _frame++;
    if (_frame / 5 >= 9) {
        _frame = 0;
    }
    SDL_Rect renderQuad = { _rect.x,_rect.y,WIDTH_BOSS,HEIGHT_BOSS };
    SDL_RenderCopy(screen, _object, &_clip[_frame / 5], &renderQuad);
}
//tạo đạn
void Boss::MakeBullet(SDL_Renderer* screen) {
    for (int i = 0; i < bullet_list.size(); i++) {
        bullet* p_bullet = bullet_list.at(i);
        if (p_bullet) {
            if (p_bullet->get_is_move()) {
                p_bullet->Render(screen);
                p_bullet->HandleMoveBossBullet(SCREEN_WIDTH, SCREEN_HEIGHT + this->_rect.y);
            }
            else {
                p_bullet->SetRect(this->_rect.x + WIDTH_BOSS / 2 - p_bullet->GetRect().w / 2, this->_rect.y + HEIGHT_BOSS);
                p_bullet->set_is_move(true);
            }
        }
    }
}
//thi triển đạn
void Boss::InitBullet(bullet* p_bullet, SDL_Renderer* screen) {
    if (p_bullet != NULL) {
        if (p_bullet->loadImage("image//boss_bullet.png", screen)) {
            p_bullet->set_is_move(true);
            p_bullet->SetRect(this->_rect.x + WIDTH_BOSS / 2 - p_bullet->GetRect().w / 2, this->_rect.y + HEIGHT_BOSS);
            p_bullet->set_y_val(BOSS_BULLET_SPEED);
            bullet_list.push_back(p_bullet);
        }
    }
}


//hướng di chuyển của boss
void Boss::Move() {
    _rect.y += y_val;
    if (_status.turn_left) {
        _rect.x -= x_val;
    }
    if (_status.turn_right) {
        _rect.x += x_val;
    }
    if (_status.turn_up) {
        _rect.y -= 2 * y_val;
    }

    if (_rect.y > SCREEN_HEIGHT - HEIGHT_BOSS) {
        _status.turn_up = 1;
        _status.turn_down = 0;
    }
    else if (_rect.y < 0) {
        _status.turn_down = 1;
        _status.turn_up = 0;
    }
    if (_rect.x <= 0) {
        _status.turn_right = 1;
        _status.turn_left = 0;
    }
    else if (_rect.x >= SCREEN_WIDTH - WIDTH_BOSS) {
        _status.turn_left = 1;
        _status.turn_right = 0;
    }
}
//thanh máu của boss
void Boss::show_heart_boss(SDL_Renderer* screen, int x, int y, int w, int h) {
    SDL_Rect fill_rect = { x,y,w,h };
    SDL_SetRenderDrawColor(screen, 255, 0, 0, 255);
    SDL_RenderFillRect(screen, &fill_rect);
}