#include <iostream>
#include "List.h"
#include "Player.h"

int main() {
    /*// ---- Part 1: required test harness, do not modify ----
    std::cout << "== List<int>: addAnywhere / deleteAnywhere / reverse =="
              << std::endl;
    std::unique_ptr<List<int>> nums = makeList<int>();
    nums->addFront(new int(10));
    nums->addFront(new int(20));
    nums->addFront(new int(30));
    nums->print();
    nums->addAnywhere(1, new int(99));
    nums->print();
    nums->deleteAnywhere(2);
    nums->print();
    nums->reverse();
    nums->print();

    std::cout << std::endl << "== List<int>: concat ==" << std::endl;
    std::unique_ptr<List<int>> more = makeList<int>();
    more->addFront(new int(2));
    more->addFront(new int(1));
    more->print();
    nums->concat(more.get());
    nums->print();
    more->print(); */

    // ---- Part 2: your Uno scene goes below ----
    std::unique_ptr<List<Player>> table1 = makeList<Player>();

    table1->addFront(new Player(1, "player1"));
    table1->addFront(new Player(2, "player2"));
    table1->addFront(new Player(3, "player3"));
    table1->print();

    table1->addAnywhere(2, new Player(4, "player4"));
    table1->print();

    table1->reverse();
    table1->print();

    table1->deleteAnywhere(3);
    table1->print();

    std::unique_ptr<List<Player>> table2 = makeList<Player>();

    table2->addFront(new Player(5, "player5"));
    table2->addFront(new Player(6, "player6"));
    table2->addFront(new Player(7, "player7"));
    table2->print();

    table1->concat(table2.get());
    table1->print();
    table2->print();

    return 0;
}
