#include "Automata.h"

int main() {
    Automata automata;
    automata.getState();
    automata.on();
    automata.getMenu();

    automata.coin(30);
    automata.coin(10);
    automata.choice(3);
    automata.check();

    automata.cook();
    automata.finish();

    automata.off();

    return 0;
}