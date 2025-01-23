#pragma once
#include "sessions/sessions.h"
#include <iostream>
#include <ryml/ryml.hpp>

namespace serialization {
ryml::Tree serializeSession(sessions::Session s);
}
