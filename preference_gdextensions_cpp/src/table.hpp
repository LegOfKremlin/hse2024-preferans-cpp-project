#ifndef TABLE_HPP_
#define TABLE_HPP_

#include <vector>
#include <algorithm>
#include <random>

#include "player.hpp"
#include "card.hpp"
#include "typing.hpp"

namespace godot{

class Table : public godot::Node {
    GDCLASS(Table, godot::Node)

public:
    std::vector<Card*> deck;
    std::vector<Card*> playedCards;
    std::vector<Card*> talon;
    std::vector<Player*> players;
    Player* currentPlayer;
    Player* dealer;
    int dealerIndex;

    static void _bind_methods();

    Table();
    ~Table();

    void _init();

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

} // namespace godot

#endif // TABLE_HPP_
