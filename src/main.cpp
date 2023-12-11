#include <glog/logging.h>  // LOG(*)

#include "Card.h"         // Card
#include "Transaction.h"  // Transaction

int main() {
    // Init glog
    if (!google::IsGoogleLoggingInitialized()) {
        FLAGS_logtostderr = true;  // Log messages to stderr instead of logfiles
        google::InitGoogleLogging("CICDExperiment");
    }

    // Construct card expireTime (2100/08/15 13:32:08)
    std::chrono::year_month_day expireDate(
        std::chrono::year(2100), std::chrono::August, std::chrono::day(15));
    std::chrono::hh_mm_ss expireTimeOfDate(
        std::chrono::hours(13) + std::chrono::minutes(32) + std::chrono::seconds(8));
    std::chrono::time_point<std::chrono::high_resolution_clock> expireTime(
        std::chrono::sys_days{expireDate} + expireTimeOfDate.to_duration());

    /**
     * Card
     *  ExpireTime: 2100/08/15 13:32:08
     *  Balance   : 100
     */
    Card card(expireTime, 100);
    card.logInfo();

    Transaction entryTransaction(Transaction::TransactionType::GateEntry, 19, card);
    entryTransaction.processTransaction();

    card.logInfo();

    Transaction exitTransaction(Transaction::TransactionType::GateExit, 8, card);
    exitTransaction.processTransaction();

    card.logInfo();

    google::ShutdownGoogleLogging();
    return EXIT_SUCCESS;
}
