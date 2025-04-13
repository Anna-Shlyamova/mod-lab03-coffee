//"Copyright 2025 Owner"
#ifndef INCLUDE_AUTOMATA_H_
#define INCLUDE_AUTOMATA_H_

#include "States.h"
#include <string>
#include <vector>

class Automata {
 private:
    int cash;
    int currentDrinkIndex;
    STATES state;
    std::vector<std::string> menu;
    std::vector<int> prices;

 public:
    Automata();
    void on();
    void off();
    void coin(int amount);
    void choice(int itemIndex);
    void getMenu() const;
    void getState() const;
    void check();
    void cancel();
    void cook();
    void finish();
};

#endif