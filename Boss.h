#ifndef Boss_h
#define Boss_h

#include <vector>
#include "Base.h"
#include "Bullet.h"
#include "Explosion.h"
#include "Default.h"


#define WIDTH_BOSS 400
#define HEIGHT_BOSS 234
#define BOSS_SPEED 1
#define BOSS_BULLET_SPEED 10


class Boss : public base {
public:
	Boss();
	~Boss();

	void set_x_val(const int& xVal) {
		x_val = xVal;
	}
	void set_y_val(const int& yVal) {
		y_val = yVal;
	}
	int get_x_val()const {
		return x_val;
	}
	int get_y_val()const {
		return y_val;
	}
	void Move();
	void Show(SDL_Renderer* screen);
	void set_clip();
	SDL_Rect GetRectFrame();

	void set_bullet_list(vector<bullet*> BulletList) {
		bullet_list = BulletList;
	}
	vector <bullet*> get_bullet_list() {
		return bullet_list;
	}
	void InitBullet(bullet* p_bullet, SDL_Renderer* screen);
	void MakeBullet(SDL_Renderer* screen);


	void set_heart(const float& Heart) { _heart = Heart; }
	float get_heart()const { return _heart; }
	void Decrease(const float& bullet_damage) { _heart -= bullet_damage; }
	void show_heart_boss(SDL_Renderer* screen, int x, int y, int w, int h);

private:
	float _heart;
	std::vector<bullet*> bullet_list;

	int x_val;
	int y_val;

	StatusSaucer _status;
	int _frame;
	SDL_Rect _clip[9];

};


#endif
