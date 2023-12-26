#include "utils.h"
#include <cstdlib>
#include <ctime>

int generateRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int drawCard() {
    return rand() % 10 + 1;
}

bool flipCoin() {
    return rand() % 2 == 0;
}

