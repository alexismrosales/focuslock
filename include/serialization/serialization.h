#pragma once
#include "sessions/sessions.h"
#include <iostream>
#include <ryml/ryml.hpp>

namespace serialization {
ryml::Tree serializeSession(sessions::Session s);
ryml::Tree serializeSessions(std::vector<sessions::Session> sessions);
std::vector<sessions::Session> deserializeSessions(ryml::substr t);
} // namespace serialization
