#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <vector>
#include <algorithm>
#include <random>

#include "card.hpp"
#include "typing.hpp"

class Player {
private:
    Suit bidSuit;
    int bidNumber;
public:
    std::string name;
    int score;
    int trickCount;
    int bullet;
    int mountain;
    int whist;
    std::vector<Card*> hand;

    Player();
    ~Player();

    void discard();
    Card* playCard();
    void showCards();
    bool decideWhist();
	void incrementTrickCount();
	int getTrickCount();
	void awardPoints();
	void penalizePoints(int trickCount);
	void resetTrickCount();
    void revealCards();
    TradeResult makeBid(TradeResult highestBid, bool isFirstBid);
    Card* playCardInResponseTo(Suit leadSuit, Suit trumpSuit);
    Suit getBidSuit() const {
        return bidSuit;
    }

    int getBidNumber() const {
        return bidNumber;
    }
};

#endif // PLAYER_HPP_