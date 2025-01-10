#include "catch2/catch.hpp"
#include "flock/flock.hpp"

TEST_CASE("add_two", "[Focuslock]") {
  Focuslock flock;
  REQUIRE(flock.add_two(0) == 2);
}
