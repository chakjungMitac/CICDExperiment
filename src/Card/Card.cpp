#include "Card.h"

#include <iomanip>  // std::put_time

#include <glog/logging.h>  // LOG(*)

Card::Card(const ExpireTime& expireTime, const int& balance)
    : expireTime(expireTime), balance(balance) {}

const Card::ExpireTime& Card::getExpireTime() { return expireTime; }

const int& Card::getBalance() { return balance; }

void Card::setBalance(const int& balance) { this->balance = balance; }

const Card::CardStatus& Card::getCardStatus() { return cardStatus; }

void Card::setCardStatus(const CardStatus& cardStatus) {
    if (cardStatus != InTransit) {
        transitStationNums.InboundStation = 0;
        transitStationNums.OutboundStation = 0;
    }

    this->cardStatus = cardStatus;
}

const Card::TransitStationNums& Card::getTransitStationNums() {
    return transitStationNums;
}

void Card::setTransitStationNums(const TransitStationNums& transitStationNums) {
    this->transitStationNums = transitStationNums;
}

void Card::logInfo() {
    LOG(INFO) << "=================== Card Info ===================";

    // Log ExpireTime
    time_t expireTime_time_t =
        std::chrono::high_resolution_clock::to_time_t(expireTime);
    LOG(INFO) << "ExpireTime: "
              << std::put_time(std::gmtime(&expireTime_time_t), "%F %T");

    // Log Balance
    LOG(INFO) << "Balance   : " << balance;

    // Log CardStatus
    LOG(INFO) << "CardStatus: " << cardStatus;

    // Log TransitStationNums
    LOG(INFO) << "TransitStationNums";
    LOG(INFO) << "   Inbound: " << transitStationNums.InboundStation;
    LOG(INFO) << "  Outbound: " << transitStationNums.OutboundStation;

    LOG(INFO) << "=================================================";
}
