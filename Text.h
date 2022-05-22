#ifndef Text_h
#define Text_h

#include "Base.h"
#include "Default.h"

class Text : public base {
public:
	Text();
	~Text();

	enum TEXT_COLOR {
		RED = 5,
		WHITE = 6,
		YELLOW = 7,
	};

	void SetText(const string& text) {
		_text = text;
	}
	void SetColor(const int& type);
	void loadText_showText(TTF_Font* font, SDL_Renderer* screen);




private:
	string _text;
	SDL_Color _text_color;
};


#endif // !Text_h;

