#include <memory>
#include <gtest/gtest.h>
#include "guards.hpp"

namespace game {
namespace test {

namespace GT = ::testing;

TEST(guards_test, is_game_timeout_false) {
    //given
    auto ticks = std::make_shared<time_ticks>(0);
    auto game_time = 10;
    is_game_timeout guard(ticks, game_time);

    //when && then
    EXPECT_FALSE(guard(time_tick()));
}

TEST(guards_test, is_game_timeout_true) {
    //given
    auto ticks = std::make_shared<time_ticks>(15);
    auto game_time = 10;
    is_game_timeout guard(ticks, game_time);

    //when && then
    EXPECT_TRUE(guard(time_tick()));
}

TEST(guards_test, is_key_false) {
    //given
    is_key<42> guard;
    SDL_Event key = { };

    //when && then
    EXPECT_FALSE(guard(key_pressed()));
}

TEST(guards_test, is_key_true) {
    //given
    is_key<42> guard;
    SDL_Event key = { };
    key.key.keysym.sym = 42;

    //when && then
    EXPECT_FALSE(guard(key_pressed()));
}

} // namespace test
} // namespace game

