#include "Explosion.h"

Explosion::Explosion() {
    _frame = 16;
}
Explosion::~Explosion() {

}
//cài hiệu ứng nổ
void Explosion::set_clip() {
    for (int i = 0; i < 8; i++) {
        _clip[i].x = i * WIDTH_FRAME_EXP;
        _clip[i].y = 0;
        _clip[i].w = WIDTH_FRAME_EXP;
        _clip[i].h = HEIGHT_FRAME_EXP;
    }
}
//hiệu ứng nổ
void Explosion::Show(SDL_Renderer* screen) {
    _frame++;
    SDL_Rect renderQuad = { _rect.x ,_rect.y , WIDTH_FRAME_EXP ,HEIGHT_FRAME_EXP };
    SDL_RenderCopy(screen, _object, &_clip[_frame / 2], &renderQuad);
}