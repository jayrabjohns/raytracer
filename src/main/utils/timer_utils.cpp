#include "timer_utils.hpp"

double TimerUtils::time_proc(std::function<void(void)> func) {
  time_t start, end;

  std::time(&start);
  func();
  std::time(&end);

  double elapsed_secs = static_cast<double>(end - start);
  return elapsed_secs;
};
