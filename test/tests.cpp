// Copyright 2022 GHA Test Team

#include <gtest/gtest.h>
#include "Automata.h"

TEST(AutomataTest, InitialStateIsOff) {
    Automata automata;
    EXPECT_EQ(automata.getState(), STATES::OFF);
}

TEST(AutomataTest, TurnsOnToWait) {
    Automata automata;
    automata.on();
    EXPECT_EQ(automata.getState(), STATES::WAIT);
}

TEST(AutomataTest, CannotTurnOffDuringOperation) {
    Automata automata;
    automata.on();
    automata.coin(50);
    testing::internal::CaptureStdout();
    automata.off();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Automata can't be turn on during the work"), std::string::npos);
    EXPECT_NE(automata.getState(), STATES::OFF);
}

TEST(AutomataTest, InsertCoinInWait) {
    Automata automata;
    automata.on();
    automata.coin(30);
    EXPECT_EQ(automata.getState(), STATES::ACCEPT);
}

TEST(AutomataTest, AddMoreCoinsInAccept) {
    Automata automata;
    automata.on();
    automata.coin(20);
    testing::internal::CaptureStdout();
    automata.coin(10);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Total sum: 30"), std::string::npos);
    EXPECT_EQ(automata.getState(), STATES::ACCEPT);
}

TEST(AutomataTest, ChooseDrinkInAccept) {
    Automata automata;
    automata.on();
    automata.coin(50);
    automata.choice(1);
    EXPECT_EQ(automata.getState(), STATES::CHECK);
}

TEST(AutomataTest, ChooseInvalidDrinkFails) {
    Automata automata;
    automata.on();
    automata.coin(50);
    testing::internal::CaptureStdout();
    automata.choice(99);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Incorrect Index"), std::string::npos);
}

TEST(AutomataTest, CancelOrderReturnsToWait) {
    Automata automata;
    automata.on();
    automata.coin(30);
    testing::internal::CaptureStdout();
    automata.cancel();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Order cancelled, refund: 30"), std::string::npos);
    EXPECT_EQ(automata.getState(), STATES::WAIT);
}

TEST(AutomataTest, CookDrinkAfterCheck) {
    Automata automata;
    automata.on();
    automata.coin(50);
    automata.choice(1);
    automata.check();
    automata.cook();
    EXPECT_EQ(automata.getState(), STATES::COOK);
}

TEST(AutomataTest, FinishResetsStateAndCash) {
    Automata automata;
    automata.on();
    automata.coin(50);
    automata.choice(1);
    automata.check();
    automata.cook();
    testing::internal::CaptureStdout();
    automata.finish();
    EXPECT_NE(output.find("Change: 10"), std::string::npos);
    EXPECT_EQ(automata.getState(), STATES::WAIT);
}

TEST(AutomataTest, CannotCookIfNotCheck) {
    Automata automata;
    automata.on();
    automata.coin(50);
    automata.cook();
    EXPECT_NE(automata.getState(), STATES::COOK);
}

TEST(AutomataTest, CannotFinishIfNotCook) {
    Automata automata;
    automata.on();
    automata.coin(50);
    automata.finish();
    EXPECT_NE(automata.getState(), STATES::WAIT);
}

TEST(AutomataTest, TurnOffFromWait) {
    Automata automata;
    automata.on();
    automata.off();
    EXPECT_EQ(automata.getState(), STATES::OFF);
}
