#include "modules/pomodoro.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <thread>

namespace pomodoro {
void printTimer(std::string minute, std::string second) {
  // command: toilet -f future "${minute} : ${second}"
  std::string toiletCommand =
      "clear && toilet -f future \"" + minute + " : " + second + "\"";
  // execute command
  system(toiletCommand.c_str());
}

// timer which recieves a callback funcion to format time output
void timer(std::chrono::minutes time,
           std::function<void(std::string minute, std::string second)>
               printTimerFunction) {
  for (int minute = time.count() - 1; minute >= 0; minute--) {
    for (int seconds = 59; seconds >= 0; seconds--) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      if (printTimerFunction) {
        std::ostringstream minStr, secStr;
        minStr << std::setw(2) << std::setfill('0') << minute;
        secStr << std::setw(2) << std::setfill('0') << seconds;
        printTimerFunction(minStr.str(), secStr.str());
      }
    }
  }
}
void startTimer(pomodoro::PomodoroContext p) {
  std::chrono::minutes workTime = p.work;
  std::chrono::minutes shortBreakTime = p.shortBreak;
  std::chrono::minutes longBreakTime = p.shortBreak;
  int cycles = p.cycles;

  // start timer
  std::cout << "Iniciando timer: " << std::endl;
  std::thread timerThread(timer, workTime, printTimer);
  timerThread.join();
}
} // namespace pomodoro
