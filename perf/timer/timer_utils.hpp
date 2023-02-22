#ifndef TIMER_H
#define TIMER_H
#define TIMER_ENABLED

#include <functional>

template<class R, class... Args>
// double timeFn(const F(func)(Args...), Args&&... args) {
double timeFn(std::function<R(Args...)> func, Args... args) {
  time_t start, end;

  time(&start);
  func(args...);
  time(&end);

  double elapsed_secs = static_cast<double>(end - start);
  return elapsed_secs;
};

double timeFn(std::function<void(void)> func) {
  time_t start, end;

  time(&start);
  func();
  time(&end);

  double elapsed_secs = static_cast<double>(end - start);
  return elapsed_secs;
};
#endif
