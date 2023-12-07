#include <gtest/gtest.h>

#include "Card.h"

class CardTest : public testing::Test {
   protected:
    CardTest() {
        // Construct card expireTime (2020/07/28 15:10:31)
        std::chrono::year_month_day expireDate(
            std::chrono::year(2020), std::chrono::July, std::chrono::day(28));
        std::chrono::hh_mm_ss expireTimeOfDate(std::chrono::hours(15) +
                                               std::chrono::minutes(10) +
                                               std::chrono::seconds(31));
        std::chrono::time_point<std::chrono::high_resolution_clock> expireTime(
            std::chrono::sys_days{expireDate} + expireTimeOfDate.to_duration());

        /**
         * Card
         *  ExpireTime: 2020/07/28 15:10:31
         *  Balance   : 31
         */
        card = std::make_unique<Card>(expireTime, 31);
    }

    std::unique_ptr<Card> card;
};

TEST_F(CardTest, ExpireTime) {
    /**
     * Starting at 2020/07/28 15:10:28
     * [0] 15:10:28 (LT)
     * [1] 15:10:29 (LT)
     * [2] 15:10:30 (LT)
     * [3] 15:10:31 (EQ)
     * [4] 15:10:32 (GT)
     * [5] 15:10:33 (GT)
     * [6] 15:10:34 (GT)
     */

    std::chrono::year_month_day date(std::chrono::year(2020), std::chrono::July,
                                     std::chrono::day(28));
    std::chrono::hh_mm_ss timeOfDate(std::chrono::hours(15) +
                                     std::chrono::minutes(10) +
                                     std::chrono::seconds(28));
    std::chrono::time_point<std::chrono::high_resolution_clock> time(
        std::chrono::sys_days{date} + timeOfDate.to_duration());

    for (unsigned char i = 0; i <= 6; ++i) {
        if (i <= 2)
            EXPECT_LT(time, card->getExpireTime());
        else if (i == 3)
            EXPECT_EQ(time, card->getExpireTime());
        else
            EXPECT_GT(time, card->getExpireTime());

        time += std::chrono::seconds(1);
    }
}

TEST_F(CardTest, Balance) {
    EXPECT_EQ(31, card->getBalance());

    // Positive
    card->setBalance(85231);
    EXPECT_EQ(85231, card->getBalance());

    // Zero
    card->setBalance(0);
    EXPECT_EQ(0, card->getBalance());

    // Negative
    card->setBalance(-956381);
    EXPECT_EQ(-956381, card->getBalance());
}

TEST_F(CardTest, CardStatus) {
    EXPECT_EQ(Card::CardStatus::Normal, card->getCardStatus());

    // InTransit
    card->setCardStatus(Card::CardStatus::InTransit);
    EXPECT_EQ(Card::CardStatus::InTransit, card->getCardStatus());

    // Normal
    card->setCardStatus(Card::CardStatus::Normal);
    EXPECT_EQ(Card::CardStatus::Normal, card->getCardStatus());

    // InTransit (TransitStationNums{108, 57})
    card->setCardStatus(Card::CardStatus::InTransit);
    card->setTransitStationNums(Card::TransitStationNums{108, 57});
    EXPECT_EQ(Card::CardStatus::InTransit, card->getCardStatus());
    EXPECT_EQ(108, card->getTransitStationNums().InboundStation);
    EXPECT_EQ(57, card->getTransitStationNums().OutboundStation);

    // Normal (TransitStationNums{0, 0})
    card->setCardStatus(Card::CardStatus::Normal);
    EXPECT_EQ(Card::CardStatus::Normal, card->getCardStatus());
    EXPECT_EQ(0, card->getTransitStationNums().InboundStation);
    EXPECT_EQ(0, card->getTransitStationNums().OutboundStation);
}

TEST_F(CardTest, TransitStationNums) {
    EXPECT_EQ(0, card->getTransitStationNums().InboundStation);
    EXPECT_EQ(0, card->getTransitStationNums().OutboundStation);

    // TransitStationNums{123, 456}
    card->setTransitStationNums(Card::TransitStationNums{123, 456});
    EXPECT_EQ(123, card->getTransitStationNums().InboundStation);
    EXPECT_EQ(456, card->getTransitStationNums().OutboundStation);

    // TransitStationNums{0, 0}
    card->setTransitStationNums(Card::TransitStationNums{0, 0});
    EXPECT_EQ(0, card->getTransitStationNums().InboundStation);
    EXPECT_EQ(0, card->getTransitStationNums().OutboundStation);
}
