#ifndef _RECT_HPP_
#define _RECT_HPP_

class Rect {
  public:
    float x;
    float y;
    float w;
    float h;
    Rect ();
    Rect (float x, float y, float w, float h);
    Rect operator+ (Rect& other);
    Rect operator- (Rect& other);
};

#endif //_RECT_HPP_