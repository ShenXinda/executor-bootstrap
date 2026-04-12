#ifndef ROBOT_COMMON_TYPE_H
#define ROBOT_COMMON_TYPE_H

#include <cstdint>

enum class Heading : int32_t {
    North = 0,
    East = 1,
    South = 2,
    West = 3
};

struct Position {
    int32_t x {0};
    int32_t y {0};
    Heading heading {Heading::North};
};

#endif