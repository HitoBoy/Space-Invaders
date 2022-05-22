#include "Boost.h"

Boost::Boost() {
	boost_type = 0;
	come_back = false;
	_frame = 0;
}

Boost::~Boost() {

}

void Boost::Show(SDL_Renderer* screen) {
	if (boost_type == 3) {
		if (come_back == true) {
			_frame++;
			if (_frame / 3 >= 25)
				_frame = 0;
			SDL_Rect renderQuad = { _rect.x,_rect.y,WIDTH_LEVEL_UP, HEIGHT_LEVEL_UP };
			SDL_RenderCopy(screen, _object, &_clip[_frame / 3], &renderQuad);
		}
	}
	else if (boost_type < 3) {
		if (come_back == true) {
			Render(screen);
		}
	}
}

void Boost::Move(const int& x_border, const int& y_border) {
	if (come_back == true) {
		_rect.y += y_val;
		if (_rect.y > y_border) {
			come_back = false;
			_rect.x = BOOST_WIDTH;
			_rect.y = BOOST_HEIGHT;
		}
	}
}

void Boost::LoadImageBoost(SDL_Renderer* screen) {
	if (boost_type == TYPE1) {
		loadImage("image//boost1.png", screen);
	}
	else if (boost_type == TYPE2) {
		loadImage("image//boost2.png", screen);
	}
	else if (boost_type == TYPE3) {
		loadImage("image//boost3.png", screen);
	}
	else if (boost_type == LEVEL_UP) {
		loadImage("image//level_up_1225.png", screen);
	}
}

void Boost::set_clip() {
	for (int i = 0; i < 25; i++) {
		_clip[i].x = i * WIDTH_LEVEL_UP;
		_clip[i].y = 0;
		_clip[i].w = WIDTH_LEVEL_UP;
		_clip[i].h = HEIGHT_LEVEL_UP;
	}
}

SDL_Rect Boost::GetRectFrame() {
	SDL_Rect rect;
	rect.x = _rect.x;
	rect.y = _rect.y;
	rect.w = WIDTH_LEVEL_UP;
	rect.h = HEIGHT_LEVEL_UP;

	return rect;

}
//ngẫu nhiên buff
int Boost::random_boost()const {
	int rand_boost_type = rand() % 5;
	rand_boost_type = rand_boost_type < 3 ? rand_boost_type : 3;
	return rand_boost_type;
}

