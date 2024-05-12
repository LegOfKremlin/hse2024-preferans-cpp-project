#ifndef CARD_HPP_
#define CARD_HPP_

#include <string>

enum class Suit { Hearts, Diamonds, Clubs, Spades };
enum class Rank { Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };

class Card {
public:
    Suit suit;
    Rank rank;

    Card();
    ~Card();

    std::string toString();
};

std::string suitToString(Suit suit);
std::string rankToString(Rank rank);
Rank stringToRank(const std::string& rankString);
Suit stringToSuit(const std::string& suitString);

#endif // CARD_HPP_
