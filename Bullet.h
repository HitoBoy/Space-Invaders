#ifndef bullet_h
#define bullet_h

#include "Base.h"
#include "Default.h"

class bullet : public base {
public:
	bullet();
	~bullet();

	void set_x_val(const int& xVal){
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
	void set_is_move(const bool& isMove) {
		is_move = isMove;
	}
	bool get_is_move()const {
		return is_move;
	}
	void set_bullet_type(const int& BulletType){
		bullet_type = BulletType;
	}
	bool get_bullet_type()const {
		return bullet_type;
	}

	void HandleMoveSpaceshipBullet();
	void HandleMoveSaucerBullet();
	void HandleMoveBossBullet(const int& x_border, const int& y_border);
	void LoadImgBullet(SDL_Renderer* screen, int bullet_level);





private:
	int x_val;
	int y_val;
	bool is_move;
	int bullet_type;
};


#endif
