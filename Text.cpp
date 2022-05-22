#include "Text.h"

Text::Text() {
    _rect.x = 0;
    _rect.y = 0;
    _text_color.r = 255;
    _text_color.g = 255;
    _text_color.b = 255;
}
Text::~Text() {

}
//chữ
void Text::SetColor(const int& type) {
    if (type == RED) {
        _text_color = { 255,0,0 };
    }
    else if (type == WHITE) {
        _text_color = { 255,255,255 };
    }
    else if (type == YELLOW) {
        _text_color = { 255,255,0 };
    }
}
void Text::loadText_showText(TTF_Font* font, SDL_Renderer* screen) {
    Clean();
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, _text.c_str(), _text_color);
    if (textSurface != NULL) {
        _object = SDL_CreateTextureFromSurface(screen, textSurface);
        if (_object != NULL) {
            _rect.w = textSurface->w;
            _rect.h = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }

    Render(screen);
}