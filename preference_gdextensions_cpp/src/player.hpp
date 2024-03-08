#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/array.hpp>
#include <vector>
#include <algorithm>
#include <random>

//#include "card.hpp"

namespace godot{

//enum class Bid {
//    Pass,
//    Misere
//};

class Player : public Node {
    GDCLASS(Player, Node)

public:
    std::string name;
    int score;
    int bullet;
    int mountain;
    int whist;
    //std::vector<Card> hand;
    //Bid currentBid;

    static void _bind_methods();

    Player();
    ~Player();

    void _init();

    //void discard(Card card1, Card card2);
    //Bid bid(Bid highestBid, bool isFirstBid);
    //Card playCard(Card card);
    //void openCards();
    //bool outOfCards();
    //void makeMove();
    //void incrementScore();
    //int countTricks();
    //void lose();
    //void win();
};

} // namespace godot

#endif // PLAYER_HPP_