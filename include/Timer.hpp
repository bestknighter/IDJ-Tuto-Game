#ifndef _TIMER_HPP_
#define _TIMER_HPP_

class Timer {
  public:
    Timer ();
    void Update (float dt);
    void Restart ();
    float Get ();
  private:
    float time;
};

#endif // _TIMER_HPP_
