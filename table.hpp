#ifndef TABLE_HPP_
#define TABLE_HPP_

#include <vector>
#include <algorithm>
#include <random>

#include "player.hpp"
#include "card.hpp"
#include "typing.hpp"

class Table {
public:
    std::vector<Card*> deck;
    std::vector<Card*> playedCards;
    std::vector<Card*> talon;
    std::vector<Player*> players;
    Player* currentPlayer;
    Player* dealer;
    Suit trumpSuit;
    int dealerIndex;

    Table();
    ~Table();

    void shuffleDeck();
    void cutDeck();
    void addPlayer(Player* player);
    void dealCards();
    void startNewRound();
    int handleTrade();
    Player* determineTrickWinner();
    bool checkContractFulfillment(Player* player);
    void handleCardPlayed(Card* card);
    void handleRaspasyPlay();
    void handleMiserePlay(Player* player);
    void handleWhistPlay(Player* player);
};

#endif // TABLE_HPP_