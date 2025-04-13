// Copyright 2022 GHA Test Team

#include <gtest/gtest.h>
#include "Automata.h"

TEST_F(AutomataTest, InitialStateIsOff) {
    Automata b;
    EXPECT_EQ(b.getCurrentState(), STATES::OFF);
}

TEST_F(AutomataTest, TurnsOnToWait) {
    EXPECT_EQ(a.getCurrentState(), STATES::WAIT);
}

TEST_F(AutomataTest, CannotTurnOffDuringOperation) {
    a.coin(50);
    a.off();
    EXPECT_NE(a.getCurrentState(), STATES::OFF);
}

TEST_F(AutomataTest, InsertCoinInWait) {
    a.coin(30);
    EXPECT_EQ(a.getCash(), 30);
    EXPECT_EQ(a.getCurrentState(), STATES::ACCEPT);
}

TEST_F(AutomataTest, AddMoreCoinsInAccept) {
    a.coin(20);
    a.coin(10);
    EXPECT_EQ(a.getCash(), 30);
    EXPECT_EQ(a.getCurrentState(), STATES::ACCEPT);
}

TEST_F(AutomataTest, ChooseDrinkInAccept) {
    a.coin(50);
    a.choice(1);
    EXPECT_EQ(a.getCurrentDrinkIndex(), 1);
    EXPECT_EQ(a.getCurrentState(), STATES::CHECK);
}

TEST_F(AutomataTest, ChooseInvalidDrinkFails) {
    a.coin(50);
    a.choice(99);
    EXPECT_EQ(a.getCurrentDrinkIndex(), -1);
    EXPECT_EQ(a.getCurrentState(), STATES::ACCEPT);
}

TEST_F(AutomataTest, CheckSufficientFunds) {
    a.coin(50);
    a.choice(1);
    a.check();
    EXPECT_EQ(a.getCurrentState(), STATES::CHECK);
}

TEST_F(AutomataTest, CheckInsufficientFunds) {
    a.coin(10);
    a.choice(2);
    a.check();
    EXPECT_EQ(a.getCurrentState(), STATES::ACCEPT);
}

TEST_F(AutomataTest, CancelOrderReturnsToWait) {
    a.coin(30);
    a.cancel();
    EXPECT_EQ(a.getCash(), 0);
    EXPECT_EQ(a.getCurrentState(), STATES::WAIT);
}

TEST_F(AutomataTest, CookDrinkAfterCheck) {
    a.coin(50);
    a.choice(1);
    a.check();
    a.cook();
    EXPECT_EQ(a.getCurrentState(), STATES::COOK);
}

TEST_F(AutomataTest, FinishResetsStateAndCash) {
    a.coin(50);
    a.choice(1);
    a.check();
    a.cook();
    a.finish();
    EXPECT_EQ(a.getCurrentState(), STATES::WAIT);
    EXPECT_EQ(a.getCash(), 0);
}

TEST_F(AutomataTest, CannotCookIfNotCheck) {
    a.coin(50);
    a.cook();
    EXPECT_NE(a.getCurrentState(), STATES::COOK);
}

TEST_F(AutomataTest, CannotFinishIfNotCook) {
    a.coin(50);
    a.finish();
    EXPECT_NE(a.getCurrentState(), STATES::WAIT);
}

TEST_F(AutomataTest, TurnOffFromWait) {
    a.off();
    EXPECT_EQ(a.getCurrentState(), STATES::OFF);
}
