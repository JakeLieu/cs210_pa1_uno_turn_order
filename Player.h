#pragma once
#include <ostream>
#include <string>
#include "Stack.h"
#include "Card.h"
#include <random>

class Player {
public:
    Player(int id, const std::string& name)
        : id_(id), name_(name) {}

    bool operator==(const Player& other) const {
        return id_ == other.id_;
    }

    friend std::ostream& operator<<(std::ostream& out, const Player& p) {
        return out << p.id_ << " " << p.name_;
    }

    // New for Card.h extra credit
    void drawCard() {
        std::string colors[4] = {"Red", "Blue", "Green", "Yellow"};

        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<int> randomColor(0, 3);
        std::uniform_int_distribution<int> randomRank(1, 10);
        std::string color = colors[randomColor(gen)];
        int rankNum = randomRank(gen);

        std::string rank;
        if (rankNum == 10) {
            rank = "reverse";
        }
        else {
            rank = std::to_string(rankNum);
        }

        hand_.push(new Card(color, rank));
    }

    void playCard() {
        Card* playedCard = hand_.pop();

        if (playedCard != nullptr) {
            std::cout << name_ << " played " << *playedCard << std::endl;
        }

        delete playedCard;
    }

    void printHand() const {
        hand_.print();
    }

private:
    int id_;
    std::string name_;

    // new for Card.h extra credit
    Stack<Card> hand_;
};
