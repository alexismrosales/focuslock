#pragma once
#include "sessions/sessions.h"
#include <iostream>
#include <ryml/ryml.hpp>

namespace serialization {
ryml::Tree serializeSession(sessions::Session s);
ryml::Tree serializeSessions(std::vector<sessions::Session> sessions);

sessions::Session deserializeSession(ryml::substr t);
std::vector<sessions::Session> deserializeSessions(ryml::substr t);

void saveTreeToSession(sessions::Session &s, ryml::ConstNodeRef node);
void saveSessionToTree(sessions::Session s, ryml::NodeRef &root);
} // namespace serialization
