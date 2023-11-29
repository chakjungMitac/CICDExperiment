#include "Card.h"

#include <iomanip>  // std::put_time

#include <glog/logging.h>  // LOG(*)

Card::Card(const ExpireTime& expireTime, const int& balance)
    : expireTime(expireTime), balance(balance) {}

const Card::ExpireTime& Card::getExpireTime() { return expireTime; }

const int& Card::getBalance() { return balance; }

void Card::setBalance(const int& balance) { this->balance = balance; }

void Card::logInfo() {
    LOG(INFO) << "=================== Card Info ===================";

    // Log ExpireTime
    time_t expireTime_time_t =
        std::chrono::high_resolution_clock::to_time_t(expireTime);
    LOG(INFO) << "ExpireTime: "
              << std::put_time(std::gmtime(&expireTime_time_t), "%F %T");

    // Log balance
    LOG(INFO) << "Balance: " << balance;

    LOG(INFO) << "=================================================";
}
