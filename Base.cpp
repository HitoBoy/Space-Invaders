#include "base.h";

//các lệnh tạo hình ảnh và giải phóng
base::base() {
	_object = NULL;
	_rect.x = 0;
	_rect.y = 0;
	_rect.w = 0;
	_rect.h = 0;
}

base::~base() {
	Clean();
}

bool base::loadImage(string path, SDL_Renderer* screen) {
	Clean();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadSurface = IMG_Load(path.c_str());
    if (loadSurface != NULL) {
        SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        newTexture = SDL_CreateTextureFromSurface(screen, loadSurface);
        if (newTexture != NULL) {
            _rect.w = loadSurface->w;
            _rect.h = loadSurface->h;
        }
        SDL_FreeSurface(loadSurface);
    }
    _object = newTexture;
    return _object != NULL;
}
void base::Render(SDL_Renderer* screen, const SDL_Rect* clip){
    SDL_Rect renderQuad = {_rect.x, _rect.y, _rect.w, _rect.h};
    SDL_RenderCopy(screen, _object, clip, &renderQuad);
}
void base::Clean() {
    if (_object != NULL) {
        SDL_DestroyTexture(_object);
        _object = NULL;
        _rect.w = 0;
        _rect.h = 0;
    }
}


