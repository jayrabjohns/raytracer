#ifndef TIMER_H
#define TIMER_H
#define TIMER_ENABLED

#include <ctime>
#include <functional>

struct TimerUtils {
  template<class R, class... Args>
  static double time_func(std::function<R(Args...)> func, Args... args) {
    time_t start, end;

    std::time(&start);
    func(args...);
    std::time(&end);

    double elapsed_secs = static_cast<double>(end - start);
    return elapsed_secs;
  };

  static double time_proc(std::function<void(void)> func);
};
#endif
