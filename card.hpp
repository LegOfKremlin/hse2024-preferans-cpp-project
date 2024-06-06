#ifndef CARD_HPP_
#define CARD_HPP_

enum class Suit { Hearts, Diamonds, Clubs, Spades };
enum class Rank { Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };

class Card {
public:
    Suit suit;
    Rank rank;

    Card();
    ~Card();
};

#endif // CARD_HPP_