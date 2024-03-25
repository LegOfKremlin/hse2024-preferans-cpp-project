#ifndef CARD_HPP_
#define CARD_HPP_

#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/node.hpp>

namespace godot {

    enum class Suit { Hearts, Diamonds, Clubs, Spades };
    enum class Rank { Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };

    class Card : public godot::Object {
        GDCLASS(Card, godot::Object)

    public:
        Suit suit;
        Rank rank;

        static void _bind_methods();

        Card();
        ~Card();

        void _init();
    };

} // namespace godot

#endif // CARD_HPP_