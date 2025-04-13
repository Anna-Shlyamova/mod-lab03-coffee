//"Copyright 2025 Owner"

#include "Automata.h"
#include "States.h"
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;

Automata::Automata() : cash(0), state(STATES::OFF), currentDrinkIndex(-1) {
    menu = { "Tea", "Coffee", "Latte", "Cappuchino" };
    prices = { 30, 40, 50, 35 };
}

void Automata::on() {
    if (state == STATES::OFF) {
        state = STATES::WAIT;
        cout << "Automata on wait.\n";
    } else {
        state = STATES::WAIT;
        cout << "Automata has been already on wait.\n";
    }
}

void Automata::off() {
    if (state == STATES::WAIT) {
        state = STATES::OFF;
        cout << "Automata off.\n";
    } else if (state == STATES::OFF) {
        cout << "Automata has been already off.\n";
    } else {
        cout << "Automata can't be turn on during the work.\n";
    }
}

void Automata::getMenu() const {
    if (state != STATES::OFF) {
        for (int i = 0; i < menu.size(); i++) {
            cout << menu[i] << ": " << prices[i] << "\n";
        }
    } else {
        cout << "Automata off.\n";
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
        cout << "Total sum: " << cash << "\n";
    } else {
        cout << "Cash acceptance is not available.\n";
    }
}

void Automata::choice(int itemIndex) {
    if (state == STATES::ACCEPT && itemIndex >= 0 && itemIndex < menu.size()) {
        state = STATES::CHECK;
        currentDrinkIndex = itemIndex;
    } else if (state == STATES::ACCEPT) {
        cout << "Incorrect Index\n";
    } else {
        cout << "The automata must be in the ACCEPT state.\n";
    }
}

void Automata::check() {
    if (state == STATES::CHECK) {
        if (cash >= prices[currentDrinkIndex]) {
            cout << "Your drink " << menu[currentDrinkIndex]
                << " Price: " << prices[currentDrinkIndex]
                << " Balance of money: "
                << cash - prices[currentDrinkIndex] << "\n";
        } else {
            cout << "Insufficient funds.\n";
        }
    } else {
        cout << "The automata must be in the CHECK state.\n";
    }
}

void Automata::cook() {
    if (state == STATES::CHECK) {
        state = STATES::COOK;
        cout << "Cooking the drink: " << menu[currentDrinkIndex] << "\n";
    } else {
        cout << "The automata must be in the CHECK state.\n";
    }
}

void Automata::cancel() {
    if (state == STATES::CHECK || state == STATES::ACCEPT) {
        state = STATES::WAIT;
        cout << "Order cancelled, refund: " << cash << "\n";
        cash = 0;
        currentDrinkIndex = -1;
    } else {
        cout << "The automata must be in the CHECK or ACCEPT state.\n";
    }
}

void Automata::finish() {
    if (state == STATES::COOK) {
        state = STATES::WAIT;
        cout << "Your drink is ready.\n";
        if (cash > prices[currentDrinkIndex]) {
            cout << "Change: " << cash - prices[currentDrinkIndex] << "\n";
        }
        cash = 0;
        currentDrinkIndex = -1;
    } else {
        cout << "The automata must be in the COOK state.\n";
    }
}
