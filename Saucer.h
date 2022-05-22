#ifndef Chicken_h
#define Chicken_h

#include <vector>
#include "base.h"
#include "bullet.h"
#include "Explosion.h"
#include "Default.h"


#define WIDTH_SAUCER 150
#define HEIGHT_SAUCER 65
#define SAUCER_SPEED 1
#define SAUCER_BULLET_SPEED 2

class Saucer : public base {
public:
    Saucer();
    ~Saucer();

    void set_x_val(const int& Xval) {
       x_val = Xval;
    }
    void set_y_val(const int& Yval) {
       y_val = Yval;
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

    void set_bullet_list(std::vector<bullet*> bullet_list) {
       bullet_list = bullet_list;
    }
    std::vector<bullet*> get_bullet_list() {
       return bullet_list;
    }
    void InitBullet(bullet* p_bullet, SDL_Renderer* screen);
    void HandleBullet(SDL_Renderer* screen);
    void RemoveBullet(const int& idx);

    void set_heart(const float& Heart) {
        _heart = Heart;
    }
    float get_heart()const { 
        return _heart; 
    }
    void Decrease(const float& bullet_damage) {
        _heart -= bullet_damage;
    }

    void set_come_back(const bool& comeback) {
        come_back = comeback;
    }
    bool get_come_back()const {
        return come_back;
    }
    void set_status_right();


private:
    float _heart;
    std::vector<bullet*> bullet_list;

    int x_val;
    int y_val;

    StatusSaucer _status;
    int _frame;
    SDL_Rect _clip[1];
    bool come_back;
};



#endif