#include "Transaction.h"

#include <glog/logging.h>  // LOG(*)

#include "Card.h"

Transaction::Transaction(const TransactionType& transactionType,
                         const unsigned int& stationNum, Card& card)
    : transactionType(transactionType), stationNum(stationNum), card(card) {}

const Transaction::TransactionType& Transaction::getTransactionType() {
    return transactionType;
}

const Transaction::ProcessResult& Transaction::getProcessResult() {
    return processResult;
}

Transaction::ProcessResult Transaction::processTransaction() {
    // Check ExpireTime
    if (card.getExpireTime() < std::chrono::high_resolution_clock::now()) {
        LOG(WARNING) << "Transaction Failed: Card Expired";
        processResult = ProcessResult::CardExpired;
        return processResult;
    }

    // Check RepeatedEntry
    if (transactionType == GateEntry &&
        card.getCardStatus() == Card::CardStatus::InTransit) {
        LOG(WARNING) << "Transaction Failed: Repeated Entry";
        processResult = ProcessResult::RepeatedEntry;
        return processResult;
    }

    // Check RepeatedExit
    if (transactionType == GateExit &&
        card.getCardStatus() != Card::CardStatus::InTransit) {
        LOG(WARNING) << "Transaction Failed: Repeated Exit";
        processResult = ProcessResult::RepeatedExit;
        return processResult;
    }

    // Process Transaction
    switch (transactionType) {
        case GateEntry:
            LOG(INFO) << "Processing Gate Entry Transaction...";
            card.setCardStatus(Card::CardStatus::InTransit);
            card.setTransitStationNums(Card::TransitStationNums{stationNum, 0});
            break;

        case GateExit:
            card.setTransitStationNums(Card::TransitStationNums{
                card.getTransitStationNums().InboundStation, stationNum});

            // Calculate fare
            const unsigned int fare = calculateFare();

            // Check InsufficientBalance
            if (0 > card.getBalance() || fare > (unsigned int)card.getBalance()) {
                LOG(WARNING) << "Transaction Failed: Insufficient Balance";
                processResult = ProcessResult::InsufficientBalance;
                return processResult;
            }

            LOG(INFO) << "Processing Gate Exit Transaction...";

            // Deduct fare
            card.setBalance(card.getBalance() - fare);

            // Reset CardStatus
            card.setCardStatus(Card::CardStatus::Normal);
            card.setTransitStationNums(Card::TransitStationNums{0, 0});
            break;
    }

    processResult = ProcessResult::Success;
    return processResult;
}

unsigned int Transaction::calculateFare() {
    const Card::TransitStationNums& transitStationNums =
        card.getTransitStationNums();

    // Calculate Absolute distance
    const unsigned int travelDistance =
        transitStationNums.InboundStation > transitStationNums.OutboundStation
            ? transitStationNums.InboundStation - transitStationNums.OutboundStation
            : transitStationNums.OutboundStation - transitStationNums.InboundStation;

    LOG(INFO) << "Travel Distance: " << travelDistance << " = |"
              << transitStationNums.InboundStation << " - "
              << transitStationNums.OutboundStation << '|';

    // $5 per Station + Base Rate $20
    const unsigned int fare = travelDistance * 5 + 20;

    LOG(INFO) << "Fare: $5 per Station + Base Rate $20";
    LOG(INFO) << "      $" << fare << " = $5 * " << travelDistance << " + $20";

    return fare;
}
