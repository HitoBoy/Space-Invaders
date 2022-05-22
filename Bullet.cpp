#include "Bullet.h"

bullet::bullet() {
	x_val = 0;
	y_val = 0;
	is_move = false;
	bullet_type = TYPE1;
}

bullet::~bullet() {

}
//hình ảnh của đạn
void bullet::LoadImgBullet(SDL_Renderer* screen, int bullet_level){
	if (bullet_type == TYPE1) {
		string Type1_str = "image//type1" + std::to_string(bullet_level) + ".png";
		loadImage(Type1_str, screen);
	}
    else if (bullet_type == TYPE2) {
        string Type2_str = "image//type2" + std::to_string(bullet_level) + ".png";
        loadImage(Type2_str, screen);
    }
    else if (bullet_type == TYPE3) {
        string Type3_str = "image//type3" + std::to_string(bullet_level) + ".png";
        loadImage(Type3_str, screen);
    }
}
//di chuyển đạn của tàu chiến
void bullet::HandleMoveSpaceshipBullet() {
    _rect.y += y_val;
    if (_rect.y < -_rect.h) {
        is_move = false;
    }
}
//di chuyển đạn của ufo
void bullet::HandleMoveSaucerBullet() {
    _rect.y += y_val;
    if (_rect.y > SCREEN_HEIGHT) {
        is_move = false;
    }
}
//di chuyển đạn của boss
void bullet::HandleMoveBossBullet(const int& x_border, const int& y_border) {
    _rect.y += y_val;
    if (_rect.y > y_border) {
        is_move = false;
    }
}