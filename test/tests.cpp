// Copyright 2022 GHA Test Team

#include "Automata.h"
#include <gtest/gtest.h>
#include <string>

TEST(AutomataTest, InitialStateIsOff) {
    Automata automata;
    testing::internal::CaptureStdout();
    automata.getState();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("OFF"), std::string::npos);
}

TEST(AutomataTest, TurnsOnToWait) {
    Automata automata;
    automata.on();
    testing::internal::CaptureStdout();
    automata.getState();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("WAIT"), std::string::npos);
}

TEST(AutomataTest, CannotTurnOffDuringOperation) {
    Automata automata;
    automata.on();
    automata.coin(50);
    testing::internal::CaptureStdout();
    automata.off();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Automata can't be turn on during the work"), std::string::npos);
    testing::internal::CaptureStdout();
    automata.getState();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("OFF"), std::string::npos);
}

TEST(AutomataTest, CannotTurnOffDuringOperation2) {
    Automata automata;
    automata.on();
    automata.coin(50);
    automata.off();
    testing::internal::CaptureStdout();
    automata.getState();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("OFF"), std::string::npos);
}

TEST(AutomataTest, InsertCoinInWait) {
    Automata automata;
    automata.on();
    automata.coin(30);
    testing::internal::CaptureStdout();
    automata.getState();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("ACCEPT"), std::string::npos);
}

TEST(AutomataTest, AddMoreCoinsInAccept) {
    Automata automata;
    automata.on();
    automata.coin(20);
    testing::internal::CaptureStdout();
    automata.coin(10);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Total sum: 30"), std::string::npos);
}

TEST(AutomataTest, AddMoreCoinsInAccept2) {
    Automata automata;
    automata.on();
    automata.coin(20);
    automata.coin(10);
    testing::internal::CaptureStdout();
    automata.getState();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("ACCEPT"), std::string::npos);
}

TEST(AutomataTest, ChooseDrinkInAccept) {
    Automata automata;
    automata.on();
    automata.coin(50);
    automata.choice(1);
    testing::internal::CaptureStdout();
    automata.getState();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("CHECK"), std::string::npos);
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
}

TEST(AutomataTest, CancelOrderReturnsToWait2) {
    Automata automata;
    automata.on();
    automata.coin(30);
    automata.cancel();
    testing::internal::CaptureStdout();
    automata.getState();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("WAIT"), std::string::npos);
}

TEST(AutomataTest, CookDrinkAfterCheck) {
    Automata automata;
    automata.on();
    automata.coin(50);
    automata.choice(1);
    automata.check();
    automata.cook();
    testing::internal::CaptureStdout();
    automata.getState();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("COOK"), std::string::npos);
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
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Change: 10"), std::string::npos);
}

TEST(AutomataTest, FinishResetsStateAndCash2) {
    Automata automata;
    automata.on();
    automata.coin(50);
    automata.choice(1);
    automata.check();
    automata.cook();
    automata.finish();
    testing::internal::CaptureStdout();
    automata.getState();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("WAIT"), std::string::npos);
}

TEST(AutomataTest, CannotCookIfNotCheck) {
    Automata automata;
    automata.on();
    automata.coin(50);
    automata.cook();
    testing::internal::CaptureStdout();
    automata.getState();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("COOK"), std::string::npos);
}

TEST(AutomataTest, CannotFinishIfNotCook) {
    Automata automata;
    automata.on();
    automata.coin(50);
    automata.finish();
    testing::internal::CaptureStdout();
    automata.getState();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("WAIT"), std::string::npos);
}

TEST(AutomataTest, TurnOffFromWait) {
    Automata automata;
    automata.on();
    automata.off();
    testing::internal::CaptureStdout();
    automata.getState();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("OFF"), std::string::npos);
}
