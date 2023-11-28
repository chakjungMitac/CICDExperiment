#include <glog/logging.h>  // LOG(*)

#include "Card.h"

int main() {
    // Init glog
    if (!google::IsGoogleLoggingInitialized()) {
        FLAGS_logtostderr = true;  // Log messages to stderr instead of logfiles
        google::InitGoogleLogging("CICDExperiment");
    }

    google::ShutdownGoogleLogging();
    return EXIT_SUCCESS;
}
