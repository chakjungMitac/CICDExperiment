#pragma once

#include <chrono>

class Card {
   public:
    enum CardStatus { Normal, InTransit };

    struct TransitStationNums {
        unsigned int InboundStation;
        unsigned int OutboundStation;
    };

   private:
    typedef std::chrono::time_point<std::chrono::high_resolution_clock> ExpireTime;

   public:
    Card(const ExpireTime& expireTime, const int& balance);

    const ExpireTime& getExpireTime();

    const int& getBalance();
    void setBalance(const int& balance);

    const CardStatus& getCardStatus();
    void setCardStatus(const CardStatus& cardStatus);

    const TransitStationNums& getTransitStationNums();
    void setTransitStationNums(const TransitStationNums& transitStationNums);

    void logInfo();

   private:
    ExpireTime expireTime;

    int balance;

    CardStatus cardStatus = CardStatus::Normal;

    /**
     * InTransit: (Inbound station, Outbound station)
     * Else: (0, 0)
     */
    TransitStationNums transitStationNums{0, 0};
};
