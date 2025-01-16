#include "actions/actions.h"
#include <iostream>

namespace actions {
void NewSession(std::string sessionName) {
  // crearing new session
  Session s{sessionName, // name
            {            // config
             {
                 // pomodoro (default config)
                 true,                     // enable
                 std::chrono::minutes(25), // work
                 std::chrono::minutes(5),  // shortBreak
                 std::chrono::minutes(15), // longBreak
                 4                         // cycles
             }}};
}

} // namespace actions
