#ifndef TIMER_H
#define TIMER_H

class Timer {
private:
	float time;
public:
	inline Timer (void);
	inline void Update (float dt);
	inline void Restart (void);
	inline float Get(void) const;
};

Timer::Timer(void) { time = 0.0f; }
void Timer::Update (float dt) { time += dt; }
void Timer::Restart (void) { time = 0.0f; }
float Timer::Get (void) const { return time; }

#endif


