#include <glog/logging.h>  // LOG(*)

#include "Card.h"

int main() {
    // Init glog
    if (!google::IsGoogleLoggingInitialized()) {
        FLAGS_logtostderr = true;  // Log messages to stderr instead of logfiles
        google::InitGoogleLogging("CICDExperiment");
    }

    // Construct card expireTime (2023/08/15 13:32:08)
    std::chrono::year_month_day expireDate(
        std::chrono::year(2023), std::chrono::August, std::chrono::day(15));
    std::chrono::hh_mm_ss expireTimeOfDate(
        std::chrono::hours(13) + std::chrono::minutes(32) + std::chrono::seconds(8));
    std::chrono::time_point<std::chrono::high_resolution_clock> expireTime(
        std::chrono::sys_days{expireDate} + expireTimeOfDate.to_duration());

    Card card(expireTime);
    card.logInfo();

    google::ShutdownGoogleLogging();
    return EXIT_SUCCESS;
}
