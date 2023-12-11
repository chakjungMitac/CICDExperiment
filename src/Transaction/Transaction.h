#pragma once

class Card;

class Transaction {
   public:
    enum TransactionType { GateEntry, GateExit };

    enum ProcessResult {
        Success,
        NotProcessed,
        CardExpired,
        InsufficientBalance,
        RepeatedEntry,
        RepeatedExit
    };

   public:
    Transaction(const TransactionType& transactionType,
                const unsigned int& stationNum, Card& card);

    const TransactionType& getTransactionType();

    const ProcessResult& getProcessResult();
    ProcessResult processTransaction();

   private:
    const TransactionType transactionType;

    const unsigned int stationNum;

    Card& card;

    ProcessResult processResult = ProcessResult::NotProcessed;

    unsigned int calculateFare();
};
