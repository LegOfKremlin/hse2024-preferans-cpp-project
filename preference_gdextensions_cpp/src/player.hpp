#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/array.hpp>
#include <vector>
#include <algorithm>
#include <random>

#include "card.hpp"
#include "typing.hpp"

namespace godot{

class Player : public Node {
    GDCLASS(Player, Node)

public:
    std::string name;
    int score;
    int bullet;
    int mountain;
    int whist;
    std::vector<Card> hand;
    //Bid currentBid;

    static void _bind_methods();

    Player();
    ~Player();

    void _init();

    void discard();
    Card playCard();
    bool decideWhist();
    void revealCards();
    //void openCards();
    //bool outOfCards();
    Move makeMove();
    //void incrementScore();
    //int countTricks();
    //void lose();
    //void win();
};

} // namespace godot

#endif // PLAYER_HPP_
