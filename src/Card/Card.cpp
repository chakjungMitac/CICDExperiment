#include "Card.h"

#include <iomanip>  // std::put_time

#include <glog/logging.h>  // LOG(*)

Card::Card(std::chrono::time_point<std::chrono::high_resolution_clock> expireTime)
    : expireTime(expireTime) {}

const std::chrono::time_point<std::chrono::high_resolution_clock>&
Card::getExpireTime() {
    return expireTime;
}

void Card::logInfo() {
    LOG(INFO) << "=================== Card Info ===================";

    // Log ExpireTime
    time_t expireTime_time_t =
        std::chrono::high_resolution_clock::to_time_t(expireTime);
    LOG(INFO) << "ExpireTime: "
              << std::put_time(std::gmtime(&expireTime_time_t), "%F %T");

    LOG(INFO) << "=================================================";
}
