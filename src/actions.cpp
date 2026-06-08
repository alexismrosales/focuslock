#include "actions/actions.h"
#include "modules/pomodoro.h"
#include "sessions/sessions.h"
#include <iostream>
#include <sstream>

namespace actions {

// newSession, creates a new session, first loading all sessions avalaible and
// adds the new session to the sessions and then save it
std::string newSession(std::string name) {
  // creating new session
  sessions::Session s = {name, sessions::Settings{}};
  std::vector<sessions::Session> ss = sessions::loadSessions();
  // verify session name duplication
  for (auto &session : ss) {
    if (session.name == name) {
      std::cerr << "error creating session: session name already exist"
                << std::endl;
      std::exit(EXIT_FAILURE);
    }
  }
  // add new session
  ss.push_back(s);

  sessions::saveSessions(ss);
  return "new session " + name + " created succesfully";
}

// setSession to a temporal file saved in $HOME/.local/share/focuslock if it
// is avalaible
std::string setSession(std::string name) {
  std::vector<sessions::Session> ss = sessions::loadSessions();

  // find index of session selected
  int index = sessions::findSessionIndexByName(ss, name);
  // in case session was not found
  if (index == -1) {
    std::cerr << "error obtaining temp session: session does not exists"
              << std::endl;
    std::exit(EXIT_FAILURE);
  }
  // save session
  sessions::saveTemporalSession(ss[index]);
  return "new session " + name + " created succesfully";
}

// status show the current status of the temporal session in case it exists
std::string status(std::string name) {
  // if there is an specific session
  if (name != "") {
    std::vector<sessions::Session> ss = sessions::loadSessions();
    int index = sessions::findSessionIndexByName(ss, name);
    if (index != -1) {
      return sessions::sessionInfo(ss[index], false);
    }
  } else {
    sessions::Session s = sessions::loadTemporalSession();
    if (!s.name.empty()) {
      return sessions::sessionInfo(s, true);
    }
  }
  std::cerr << "no current session set";
  return "";
}

// listSessions, first loading all sessions and then format them
std::string listSessions() {
  std::vector<sessions::Session> ss = sessions::loadSessions();
  std::string sessionsStr = "";
  // iterate over sessions
  for (int i = 0; i < ss.size(); i++) {
    sessionsStr += "[" + std::to_string(i + 1) + "] " +
                   "session:" + ss[i].name + "\n    -pomodoro:" +
                   (ss[i].settings.pomodoro.enable ? "enabled" : "disabled") +
                   "\n    -blocker: " +
                   (ss[i].settings.pomodoro.enable ? "enabled" : "disabled") +
                   "\n\n";
  }
  // remove last two line breaks
  sessionsStr.pop_back();
  sessionsStr.pop_back();
  return sessionsStr;
}

// pomodoro configuration for the temporal session
std::string pomodoro(std::unordered_map<std::string, int> args) {
  sessions::Session s = sessions::loadTemporalSession();
  if (s.name.empty()) {
    std::cerr << "error: no session set yet" << std::endl;
  }

  // saving arguments values
  for (auto [key, val] : args) {
    // convert to minutes
    std::chrono::minutes duration(val);
    if (key == "--enable") {
      s.settings.pomodoro.enable = val ? true : false;
    } else if (key == "--work") {
      s.settings.pomodoro.work = duration;
    } else if (key == "--break") {
      s.settings.pomodoro.shortBreak = duration;
    } else if (key == "--long-break") {
      s.settings.pomodoro.longBreak = duration;
    } else if (key == "cycles") {
      s.settings.pomodoro.cycles = val;
    }
  }

  std::vector<sessions::Session> ss = sessions::loadSessions();
  // find index of session selected
  int index = sessions::findSessionIndexByName(ss, s.name);
  // modifiying session selected
  ss[index] = s;
  // after modifying the current session it is saved
  sessions::saveTemporalSession(s);
  // saving all sessions with the modified session
  sessions::saveSessions(ss);
  return "pomodoro configuration updated successfully";
}

std::string block(std::unordered_map<std::string, std::string> args) {

  // loading temporal session
  sessions::Session s = sessions::loadTemporalSession();
  if (s.name.empty()) {
    std::cerr << "error: no session set yet" << std::endl;
  }

  // in case the user select list command and other command
  if (args.count("--list") && args.size() > 1) {
    std::cerr << "error: the '--list' flag must be used alone and cannot be "
                 "combined with other options.";
    std::exit(EXIT_FAILURE);
    // in case there is the list command
  } else if (args.count("--list")) {
    std::stringstream ss;
    for (int i = 0; i < s.settings.block.domains.size(); i++) {
      ss << "[" + std::to_string(i + 1) + "] " + s.settings.block.domains[i]
         << std::endl;
    }
    std::string list = ss.str();
    list.pop_back();
    return list;
  }

  // handle other cases
  for (auto [key, val] : args) {
    if (key == "--enable") {
      s.settings.pomodoro.enable = val == "true" ? true : false;
    } else if (key == "--add") {
      s.settings.block.domains.push_back(val);
    } else if (key == "--remove") { // Allow delete config by index
      int index = 0;
      std::vector<std::string> domains = s.settings.block.domains;
      while (index < domains.size()) {
        if (domains[index] == val) {
          break;
        }
        index++;
      }
      if (index >= domains.size()) {
        std::cerr << "error: domain does not exist\n";
        std::exit(EXIT_FAILURE);
      }
      // delete element from vector
      s.settings.block.domains.erase(s.settings.block.domains.begin() + index);
    }
  }
  // save modified session
  sessions::saveTemporalSession(s);
  return "block configuration was successful";
}

void start() {
  sessions::Session s = sessions::loadTemporalSession();
  pomodoro::startTimer(s.settings.pomodoro);
}
} // namespace actions
