#define RYML_SINGLE_HDR_DEFINE_NOW
#include "serialization/serialization.h"
#include "sessions/sessions.h"
#include <iostream>
#include <ryml/ryml.hpp>

namespace serialization {

// serializeSession and puts data into a tree
ryml::Tree serializeSession(sessions::Session s) {
  ryml::Tree t;
  ryml::NodeRef root = t.rootref();
  root |= ryml::MAP;
  saveSessionToTree(s, root);
  return t;
}

// serializeSessions, and iterate over all sessions to transform it into a
// single tree
ryml::Tree serializeSessions(std::vector<sessions::Session> sessions) {
  ryml::Tree t;
  ryml::NodeRef root = t.rootref();
  // creating a sequence of sessions
  root |= ryml::SEQ;
  for (auto s : sessions) {
    // root node for session
    ryml::NodeRef sessionRootNode = root.append_child();
    sessionRootNode |= ryml::MAP;
    saveSessionToTree(s, sessionRootNode);
  }
  return t;
}

// deserializeSession from a yaml string and save it into a session struct
sessions::Session deserializeSession(ryml::substr session) {
  // parsing yaml file
  ryml::Tree t = ryml::parse_in_place(ryml::to_substr(session));
  ryml::ConstNodeRef root = t.rootref(); // a const node reference

  sessions::Session s;
  saveTreeToSession(s, root);
  return s;
}

// deserializeSessions from one or more sessions and save it into a vector of
// sessions struct
std::vector<sessions::Session> deserializeSessions(ryml::substr sessions) {
  // parsing yaml file
  ryml::Tree t = ryml::parse_in_place(ryml::to_substr(sessions));
  ryml::ConstNodeRef root = t.rootref(); // a const node reference

  std::vector<sessions::Session> sessionsList;

  for (ryml::ConstNodeRef node : root.children()) {
    // just to make sure that child exists
    if (node.has_child("session")) {
      // adds data to a new session
      sessions::Session s;
      // convert tree into a session
      saveTreeToSession(s, node);
      // add session to sessions
      sessionsList.push_back(s);
    }
  }
  return sessionsList;
}

// saveTreeToSession
void saveTreeToSession(sessions::Session &s, ryml::ConstNodeRef node) {
  // name session node
  ryml::csubstr name = node["session"].val();
  std::string nameStr(name.str, name.len);
  s.name = nameStr;
  // settings->pomodoro node
  s.settings.pomodoro.enable =
      node["settings"]["pomodoro"]["enable"].val() == "true" ? true : false;
  s.settings.pomodoro.work = std::chrono::minutes(
      std::stoi(node["settings"]["pomodoro"]["work"].val().data()));
  s.settings.pomodoro.shortBreak = std::chrono::minutes(
      std::stoi(node["settings"]["pomodoro"]["short_break"].val().data()));
  s.settings.pomodoro.longBreak = std::chrono::minutes(
      std::stoi(node["settings"]["pomodoro"]["long_break"].val().data()));
  // settings->block node
  s.settings.block.enable =
      node["settings"]["block"]["enable"].val() == "true" ? true : false;
  ryml::ConstNodeRef domainsNode = node["settings"]["block"]["domains"];
  for (int i = 0; i < domainsNode.num_children(); ++i) {
    ryml::csubstr domain = domainsNode[i].val();
    std::string domainStr(domain.str, domain.len);
    s.settings.block.domains.push_back(domainStr);
  }
}

// saveSessionToTree
void saveSessionToTree(sessions::Session s, ryml::NodeRef &root) {
  // session name
  root["session"] << ryml::to_csubstr(s.name);

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
}
} // namespace serialization
