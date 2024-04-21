#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <vector>
#include <algorithm>
#include <random>

#include "card.hpp"
#include "typing.hpp"

class Player {
public:
    std::string name;
    int score;
    int bullet;
    int mountain;
    int whist;
    std::vector<Card*> hand;

    Player();
    ~Player();

    void discard();
    Card* playCard();
    bool decideWhist();
    void revealCards();
    TradeResult makeBid(TradeResult highestBid, bool isFirstBid);
    int makeMove();
    Suit getBidSuit() const;
};

#endif // PLAYER_HPP_