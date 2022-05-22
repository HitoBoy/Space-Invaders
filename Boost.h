#ifndef Boost_h
#define Boost_h

#include "Base.h"

#define BOOST_WIDTH 30
#define BOOST_HEIGHT 40
#define WIDTH_LEVEL_UP 49
#define HEIGHT_LEVEL_UP 41
#define BOOST_SPEED 6

class Boost : public base {
public:
	Boost();
	~Boost();

	void set_x_val(const int& xVal) {
		x_val = xVal;
	}
	void set_y_val(const int& yVal) {
		y_val = yVal;
	}
	int get_x_val()const{
		return x_val;
	}
	int get_y_val()const{
		return y_val;
	}

	void set_boost_type(const int& BoostType) {
		boost_type = BoostType;
	}
	int get_boost_type()const {
		return boost_type;
	}
	void set_come_back(const bool& ComeBack) {
		come_back = ComeBack;
	}
	bool get_come_back()const {
		return come_back;
	}

	void Show(SDL_Renderer* screen);
	void Move(const int& x_border, const int& y_border);
	void LoadImageBoost(SDL_Renderer* screen);

	void set_clip();
	SDL_Rect GetRectFrame();
	int random_boost()const;


private:
	int x_val;
	int y_val;

	int boost_type;
	bool come_back;

	int _frame;
	SDL_Rect _clip[25];
};


#endif // !Boost_h

