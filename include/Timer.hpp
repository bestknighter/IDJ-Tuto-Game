#ifndef TIMER_HPP
#define TIMER_HPP

class Timer {
  public:
    Timer();

    void Update( float dt );
    void Restart();
    float Get();
    
  private:
    float time;
};

#endif // TIMER_HPP
