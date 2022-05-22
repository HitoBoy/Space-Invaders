#ifndef Explosion_h
#define Explosion_h

#include "Base.h"
#include "Default.h"

#define WIDTH_FRAME_EXP 150
#define HEIGHT_FRAME_EXP 165
#define NUMBER_OF_FRAME 8

class Explosion : public base {
public:
    Explosion();
    ~Explosion();

    void set_clip();
    void Show(SDL_Renderer* screen);

    void set_frame(const int& Frame) { 
        _frame = Frame; 
    }
    int get_frame()const {
        return _frame;
    }
private:
    int _frame;
    SDL_Rect _clip[NUMBER_OF_SAUCER];


};




#endif // !Explosion_h
