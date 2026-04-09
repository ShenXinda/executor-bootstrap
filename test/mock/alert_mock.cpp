#include "alert/alert.h"
#include "mockcpp/mockcpp.hpp"

using namespace mockcpp;

void alert(AlertType type, int x, int y) {
    (void)type;
    (void)x;
    (void)y;
}