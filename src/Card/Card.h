#pragma once

#include <chrono>

class Card {
   public:
    Card(std::chrono::time_point<std::chrono::high_resolution_clock> expireTime);

    const std::chrono::time_point<std::chrono::high_resolution_clock>&
    getExpireTime();

    void logInfo();

   private:
    std::chrono::time_point<std::chrono::high_resolution_clock> expireTime;
};
