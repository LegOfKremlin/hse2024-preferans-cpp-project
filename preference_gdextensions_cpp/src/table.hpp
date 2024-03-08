#ifndef TABLE_HPP_
#define TABLE_HPP_

#include <vector>
#include <algorithm>
#include <random>

#include "player.hpp"

namespace godot{

class Table : public godot::Node {
    GDCLASS(Table, godot::Node)

public:
    //std::vector<Card> deck;
    //std::vector<Card> playedCards;
    //std::vector<Card> talon;
    godot::Array players;
    Player* currentPlayer;
    Player* dealer;

    static void _bind_methods();

    Table();
    ~Table();

    void _init();

    //void shuffleDeck();
    //void cutDeck();
    //void dealCards();
};

} // namespace godot

#endif // TABLE_HPP_