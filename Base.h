#ifndef base_h
#define base_h
#include "Default.h"

class base {
public:
	base();
	~base();

	void SetRect(const int& x, const int& y){
		_rect.x = x;
		_rect.y = y;
	}
	SDL_Rect GetRect()const {
		return _rect;
	}
	bool loadImage(string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* screen, const SDL_Rect* clip = NULL);
	void Clean();


protected:
	SDL_Rect _rect;
	SDL_Texture* _object;
};


#endif
