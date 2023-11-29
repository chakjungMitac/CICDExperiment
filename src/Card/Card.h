#pragma once

#include <chrono>

class Card {
   private:
    typedef std::chrono::time_point<std::chrono::high_resolution_clock> ExpireTime;

   public:
    Card(const ExpireTime& expireTime, const int& balance);

    const ExpireTime& getExpireTime();

    const int& getBalance();
    void setBalance(const int& balance);

    void logInfo();

   private:
    ExpireTime expireTime;

    int balance;
};
