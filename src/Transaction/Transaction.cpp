#include "Transaction.h"

#include "Card.h"

Transaction::Transaction(const TransactionType& transactionType, const Card& card)
    : transactionType(transactionType), card(card) {}

const Transaction::TransactionType& Transaction::getTransactionType() {
    return transactionType;
}

const Transaction::ProcessResult& Transaction::getProcessResult() {
    return processResult;
}

Transaction::ProcessResult Transaction::processTransaction() {
    processResult = ProcessResult::Success;
    return processResult;
}
