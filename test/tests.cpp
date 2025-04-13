// Copyright 2022 GHA Test Team

#include <gtest/gtest.h>
#include "Automata.h"

// 1. Начальное состояние OFF
TEST_F(AutomataTest, InitialStateIsOff) {
    Automata b;
    EXPECT_EQ(b.getCurrentState(), STATES::OFF);
}

// 2. Включение автомата
TEST_F(AutomataTest, TurnsOnToWait) {
    EXPECT_EQ(a.getCurrentState(), STATES::WAIT);
}

// 3. Попытка выключения не в WAIT
TEST_F(AutomataTest, CannotTurnOffDuringOperation) {
    a.coin(50);
    a.off();
    EXPECT_NE(a.getCurrentState(), STATES::OFF);
}

// 4. Внесение денег
TEST_F(AutomataTest, InsertCoinInWait) {
    a.coin(30);
    EXPECT_EQ(a.getCash(), 30);
    EXPECT_EQ(a.getCurrentState(), STATES::ACCEPT);
}

// 5. Суммирование денег
TEST_F(AutomataTest, AddMoreCoinsInAccept) {
    a.coin(20);
    a.coin(10);
    EXPECT_EQ(a.getCash(), 30);
    EXPECT_EQ(a.getCurrentState(), STATES::ACCEPT);
}

// 6. Выбор напитка
TEST_F(AutomataTest, ChooseDrinkInAccept) {
    a.coin(50);
    a.choice(1); // Кофе
    EXPECT_EQ(a.getCurrentDrinkIndex(), 1);
    EXPECT_EQ(a.getCurrentState(), STATES::CHECK);
}

// 7. Неверный индекс напитка
TEST_F(AutomataTest, ChooseInvalidDrinkFails) {
    a.coin(50);
    a.choice(99); // несуществующий
    EXPECT_EQ(a.getCurrentDrinkIndex(), -1);
    EXPECT_EQ(a.getCurrentState(), STATES::ACCEPT);
}

// 8. Проверка: достаточно средств
TEST_F(AutomataTest, CheckSufficientFunds) {
    a.coin(50);
    a.choice(1); // Кофе за 40
    a.check();
    EXPECT_EQ(a.getCurrentState(), STATES::CHECK);
}

// 9. Проверка: недостаточно средств
TEST_F(AutomataTest, CheckInsufficientFunds) {
    a.coin(10);
    a.choice(2); // Латте за 50
    a.check();
    EXPECT_EQ(a.getCurrentState(), STATES::ACCEPT);
}

// 10. Отмена заказа
TEST_F(AutomataTest, CancelOrderReturnsToWait) {
    a.coin(30);
    a.cancel();
    EXPECT_EQ(a.getCash(), 0);
    EXPECT_EQ(a.getCurrentState(), STATES::WAIT);
}

// 11. Приготовление напитка
TEST_F(AutomataTest, CookDrinkAfterCheck) {
    a.coin(50);
    a.choice(1);
    a.check();
    a.cook();
    EXPECT_EQ(a.getCurrentState(), STATES::COOK);
}

// 12. Завершение после приготовления
TEST_F(AutomataTest, FinishResetsStateAndCash) {
    a.coin(50);
    a.choice(1);
    a.check();
    a.cook();
    a.finish();
    EXPECT_EQ(a.getCurrentState(), STATES::WAIT);
    EXPECT_EQ(a.getCash(), 0);
}

// 13. Попытка приготовления не в CHECK
TEST_F(AutomataTest, CannotCookIfNotCheck) {
    a.coin(50);
    a.cook();
    EXPECT_NE(a.getCurrentState(), STATES::COOK);
}

// 14. Попытка finish не в COOK
TEST_F(AutomataTest, CannotFinishIfNotCook) {
    a.coin(50);
    a.finish();
    EXPECT_NE(a.getCurrentState(), STATES::WAIT);
}

// 15. Выключение автомата из WAIT
TEST_F(AutomataTest, TurnOffFromWait) {
    a.off();
    EXPECT_EQ(a.getCurrentState(), STATES::OFF);
}
