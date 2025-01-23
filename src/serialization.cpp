#define RYML_SINGLE_HDR_DEFINE_NOW
#include "sessions/sessions.h"
#include <iostream>
#include <ryml/ryml.hpp>

namespace serialization {
ryml::Tree serializeSession(sessions::Session s) {
  ryml::Tree t;
  ryml::NodeRef root = t.rootref();
  root |= ryml::MAP;

  // root
  ryml::NodeRef session_node = root.append_child();
  session_node.set_key("session");
  session_node.set_val(ryml::to_csubstr(s.name));

  // settings node
  ryml::NodeRef settings = root.append_child();
  settings.set_key("settings");
  settings |= ryml::MAP;

  // pomodoro node
  ryml::NodeRef pomodoro = settings.append_child();
  pomodoro.set_key("pomodoro");
  pomodoro |= ryml::MAP;
  pomodoro.append_child() << ryml::key("enable")
                          << (s.settings.pomodoro.enable ? "true" : "false");
  pomodoro.append_child() << ryml::key("work")
                          << std::to_string(s.settings.pomodoro.work.count());
  pomodoro.append_child() << ryml::key("short_break")
                          << std::to_string(
                                 s.settings.pomodoro.shortBreak.count());
  pomodoro.append_child() << ryml::key("long_break")
                          << std::to_string(
                                 s.settings.pomodoro.longBreak.count());
  pomodoro.append_child() << ryml::key("cycles")
                          << std::to_string(s.settings.pomodoro.cycles);

  // block node
  ryml::NodeRef block = settings.append_child();
  block.set_key("block");
  block |= ryml::MAP;
  block.append_child() << ryml::key("enable")
                       << (s.settings.block.enable ? "true" : "false");
  ryml::NodeRef domains_list = block.append_child();
  domains_list.set_key("domains");
  domains_list |= ryml::SEQ;
  for (const auto &domain : s.settings.block.domains) {
    domains_list.append_child() << ryml::to_csubstr(domain);
  }

  std::cout << "Árbol YAML serializado:\n";
  std::cout << ryml::emitrs_yaml<std::string>(t) << std::endl;
  return t;
}

} // namespace serialization
