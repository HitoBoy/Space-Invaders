#include "saucer.h"

Saucer::Saucer() {
    _rect.x = SCREEN_WIDTH;
    _rect.y = SCREEN_HEIGHT / 2;
    x_val = 0;
    y_val = 0;
    _status.turn_down = 0;
    _status.turn_up = 0;
    _status.turn_left = 0;
    _status.turn_right = 1;
    _frame = 0;
    _heart = 0;
    come_back = true;
}
Saucer::~Saucer() {

}
// hình ảnh của ufo
SDL_Rect Saucer::GetRectFrame() {
    SDL_Rect rect;
    rect.x = _rect.x;
    rect.y = _rect.y;
    rect.w = WIDTH_SAUCER;
    rect.h = HEIGHT_SAUCER;
    return rect;
}
void Saucer::set_clip() {
    for (int i = 0; i < 1; i++) {
        _clip[i].x = i * WIDTH_SAUCER;
        _clip[i].y = 0;
        _clip[i].w = WIDTH_SAUCER;
        _clip[i].h = HEIGHT_SAUCER;
    }
}
void Saucer::Show(SDL_Renderer* screen) {
    if (come_back == true) {
        _frame++;
        if (_frame / 5 >= 1) {
            _frame = 0;
        }
        SDL_Rect renderQuad = { _rect.x, _rect.y, WIDTH_SAUCER, HEIGHT_SAUCER };
        SDL_RenderCopy(screen, _object, &_clip[_frame / 5], &renderQuad);
    }
}
//thi triển đạn
void Saucer::HandleBullet(SDL_Renderer* screen) {

    for (int i = 0; i < bullet_list.size(); i++) {
        bullet* p_bullet = bullet_list.at(i);
        if (p_bullet) {
            if (p_bullet->get_is_move()) {
                p_bullet->Render(screen);
                p_bullet->HandleMoveSaucerBullet();
            }
            else {
                p_bullet->SetRect(this->_rect.x + WIDTH_SAUCER / 2 - p_bullet->GetRect().w / 2, this->_rect.y + HEIGHT_SAUCER);
                p_bullet->set_is_move(true);
            }
        }
    }
}
void Saucer::InitBullet(bullet* p_bullet, SDL_Renderer* screen) {
    if (p_bullet != NULL) {
        if (p_bullet->loadImage("image//saucer_bullet.png", screen)) {
            p_bullet->set_is_move(true);
            p_bullet->SetRect(this->_rect.x + WIDTH_SAUCER / 2 - p_bullet->GetRect().w / 2, this->_rect.y + HEIGHT_SAUCER);
            p_bullet->set_y_val(SAUCER_BULLET_SPEED);
            bullet_list.push_back(p_bullet);
        }
    }
}
//di chuyển ufo
void Saucer::Move() {
    if (come_back == true) {
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

        if (_rect.y > SCREEN_HEIGHT - HEIGHT_SAUCER) {
            _status.turn_up = 1;
            _status.turn_down = 0;
        }
        else if (_rect.y < 0) {
            _status.turn_down = 1;
            _status.turn_up = 0;
        }
        if (_rect.x < 0) {
            _status.turn_right = 1;
            _status.turn_left = 0;
        }
        else if (_rect.x >= SCREEN_WIDTH - WIDTH_SAUCER) {
            _status.turn_left = 1;
            _status.turn_right = 0;
        }
    }
}
void Saucer::RemoveBullet(const int& idx) {
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
void Saucer::set_status_right() {
    _status.turn_down = 0;
    _status.turn_up = 0;
    _status.turn_left = 0;
    _status.turn_right = 1;
}