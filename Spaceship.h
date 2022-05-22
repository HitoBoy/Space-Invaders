#ifndef spaceship_h
#define spaceship_h

#include <vector>
#include "Base.h"
#include "Bullet.h"
#include "Default.h"
#include <Windows.h>

#define WIDTH_PLAYER 70
#define HEIGHT_PLAYER 57
#define PLAYER_SPEED 8
#define PLAYER_HEART 3

class spaceship : public base {
public:
	spaceship();
	~spaceship();

	enum BULLET_SPEED {
		TYPE1_SPEED = 15,
		TYPE2_SPEED = 21,
		TYPE3_SPEED = 30,
	};

	void Control(SDL_Event event, SDL_Renderer* screen, Mix_Chunk* bullet_sound[4], int bullet_level, Mix_Chunk* g_sound_level_up);
	void Move();
	void Show(SDL_Renderer* screen);

	void set_bullet_list(vector<bullet*> BulletList) {
		bullet_list = BulletList;
	}
	vector <bullet*> get_bullet_list() {
		return bullet_list;
	}
	void HandleBullet(SDL_Renderer* screen);
	void RemoveBullet(const int& idx);

	void set_bullet_type(const int BulletType) {
		bullet_type = BulletType;
	}
	int get_bullet_type()const {
		return bullet_type;
	}
	void set_status(const bool& Status) {
		_status = Status;
	}
	int get_status()const {
		return _status;
	}
	
	float get_bullet_damage()const {
		return bullet_damage;
	}
	void set_heart(const int& heart) {
		_heart = heart;
	}
	int get_heart()const {
		return _heart;
	}
	void decrease_heart() {
		_heart--;
	}
	void auto_fire();



private:
	vector<bullet*> bullet_list;
	int x_val;
	int y_val;

	int bullet_type;
	int _status;
	int _heart;
	float bullet_damage;

};


#endif // !spaceship_h

