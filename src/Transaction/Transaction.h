#pragma once

class Card;

class Transaction {
   public:
    enum TransactionType { GateEntry, GateExit };

    enum ProcessResult { Success, NotProcessed, CardExpired, InsufficientBalance };

   public:
    Transaction(const TransactionType& transactionType, const Card& card);

    const TransactionType& getTransactionType();

    const ProcessResult& getProcessResult();
    ProcessResult processTransaction();

   private:
    const TransactionType transactionType;

    const Card& card;

    ProcessResult processResult = ProcessResult::NotProcessed;
};
