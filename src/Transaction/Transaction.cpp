#include "Transaction.h"

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
        processResult = ProcessResult::CardExpired;
        return processResult;
    }

    // Check RepeatedEntry
    if (transactionType == GateEntry &&
        card.getCardStatus() == Card::CardStatus::InTransit) {
        processResult = ProcessResult::RepeatedEntry;
        return processResult;
    }

    // Check RepeatedExit
    if (transactionType == GateExit &&
        card.getCardStatus() != Card::CardStatus::InTransit) {
        processResult = ProcessResult::RepeatedExit;
        return processResult;
    }

    // Process Transaction
    switch (transactionType) {
        case GateEntry:
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
                processResult = ProcessResult::InsufficientBalance;
                return processResult;
            }

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

    // $5 per Station + Base Rate $20
    return travelDistance * 5 + 20;
}
