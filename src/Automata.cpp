//"Copyright 2025 Owner"

#include "Automata.h"
#include "States.h"
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;

Automata::Automata() : cash(0), state(STATES::OFF), currentDrinkIndex(-1) {
    menu = { "Чай", "Кофе", "Латте", "Капучино" };
    prices = { 30, 40, 50, 35 };
}

void Automata::on() {
    if (state == STATES::OFF) {
        state = STATES::WAIT;
        cout << "Автомат включен.\n";
    }
    else {
        state = STATES::WAIT;
        cout << "Автомат уже включен.\n";
    }
}

void Automata::off() {
    if (state == STATES::WAIT) {
        state = STATES::OFF;
        cout << "Автомат выключен.\n";
    }
    else if (state == STATES::OFF) {
        cout << "Автомат уже выключен.\n";
    }
    else {
        cout << "Автомат нельзя выключить во время работы.\n";
    }
}

void Automata::getMenu() const {
    if (state != STATES::OFF) {
        for (int i = 0; i < menu.size(); i++) {
            cout << menu[i] << ": " << prices[i] << "\n";
        }
    }
    else {
        cout << "Автомат выключен.\n";
    }
}

void Automata::getState() const {
    switch (state) {
    case STATES::OFF:
        cout << "OFF\n";
        break;
    case STATES::WAIT:
        cout << "WAIT\n";
        break;
    case STATES::ACCEPT:
        cout << "ACCEPT\n";
        break;
    case STATES::CHECK:
        cout << "CHECK\n";
        break;
    case STATES::COOK:
        cout << "COOK\n";
        break;
    }
}

void Automata::coin(int amount) {
    if (state == STATES::WAIT || state == STATES::ACCEPT) {
        state = STATES::ACCEPT;
        cash += amount;
        cout << "Общая сумма: " << cash << "\n";
    }
    else {
        cout << "Прием денег недоступен.\n";
    }
}

void Automata::choice(int itemIndex) {
    if (state == STATES::ACCEPT && itemIndex >= 0 && itemIndex < menu.size()) {
        state = STATES::CHECK;
        currentDrinkIndex = itemIndex;
    }
    else if (state == STATES::ACCEPT) {
        cout << "Некорректный индекс.\n";
    }
    else {
        cout << "Автомат должен находиться в состоянии ACCEPT.\n";
    }
}

void Automata::check() {
    if (state == STATES::CHECK) {
        if (cash >= prices[currentDrinkIndex]) {
            cout << "Ваш напиток " << menu[currentDrinkIndex]
                << " стоимость: " << prices[currentDrinkIndex]
                << " остаток: " << cash - prices[currentDrinkIndex] << "\n";
        }
        else {
            cout << "Недостаточно средств.\n";
        }
    }
    else {
        cout << "Автомат должен находиться в состоянии CHECK.\n";
    }
}

void Automata::cook() {
    if (state == STATES::CHECK) {
        state = STATES::COOK;
        cout << "Приготовление напитка: " << menu[currentDrinkIndex] << "\n";
    }
    else {
        cout << "Автомат должен находиться в состоянии CHECK.\n";
    }
}

void Automata::cancel() {
    if (state == STATES::CHECK || state == STATES::ACCEPT) {
        state = STATES::WAIT;
        cout << "Заказ отменён, возврат: " << cash << "\n";
        cash = 0;
        currentDrinkIndex = -1;
    }
    else {
        cout << "Автомат должен находиться в состоянии CHECK или ACCEPT.\n";
    }
}

void Automata::finish() {
    if (state == STATES::COOK) {
        state = STATES::WAIT;
        cout << "Напиток готов.\n";
        if (cash > prices[currentDrinkIndex]) {
            cout << "Сдача: " << cash - prices[currentDrinkIndex] << "\n";
        }
        cash = 0;
        currentDrinkIndex = -1;
    }
    else {
        cout << "Автомат должен находиться в состоянии COOK.\n";
    }
}
