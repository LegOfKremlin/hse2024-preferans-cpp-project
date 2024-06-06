#include <stdexcept>

#include "card.hpp"

Card::Card() {
    suit = Suit::Hearts;
    rank = Rank::Seven;
}

std::string suitToString(Suit suit) {
    switch (suit) {
    case Suit::Hearts: return "Hearts";
    case Suit::Diamonds: return "Diamonds";
    case Suit::Clubs: return "Clubs";
    case Suit::Spades: return "Spades";
    default: return "Unknown suit";
    }
}

std::string rankToString(Rank rank) {
    switch (rank) {
    case Rank::Seven: return "Seven";
    case Rank::Eight: return "Eight";
    case Rank::Nine: return "Nine";
    case Rank::Ten: return "Ten";
    case Rank::Jack: return "Jack";
    case Rank::Queen: return "Queen";
    case Rank::King: return "King";
    case Rank::Ace: return "Ace";
    default: return "Unknown rank";
    }
}

Rank stringToRank(const std::string& rankString) {
    if (rankString == "Seven") return Rank::Seven;
    else if (rankString == "Eight") return Rank::Eight;
    else if (rankString == "Nine") return Rank::Nine;
    else if (rankString == "Ten") return Rank::Ten;
    else if (rankString == "Jack") return Rank::Jack;
    else if (rankString == "Queen") return Rank::Queen;
    else if (rankString == "King") return Rank::King;
    else if (rankString == "Ace") return Rank::Ace;
    else throw std::invalid_argument("Invalid rank string");
}

Suit stringToSuit(const std::string& suitString) {
    if (suitString == "Hearts") return Suit::Hearts;
    else if (suitString == "Diamonds") return Suit::Diamonds;
    else if (suitString == "Clubs") return Suit::Clubs;
    else if (suitString == "Spades") return Suit::Spades;
    else throw std::invalid_argument("Invalid suit string");
}

std::string Card::toString() {
	return rankToString(rank) + " of " + suitToString(suit);
}

Card::~Card() {}