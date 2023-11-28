#include "Card.h"

Card::Card(std::chrono::time_point<std::chrono::high_resolution_clock> expireTime)
    : expireTime(expireTime) {}

const std::chrono::time_point<std::chrono::high_resolution_clock>&
Card::getExpireTime() {
    return expireTime;
}

void Card::logInfo() {}
