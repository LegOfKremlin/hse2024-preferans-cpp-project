#include "player.hpp"
#include <iostream>
#include <string>
#include <sstream>

Player::Player() {}

Player::~Player() {
    for (auto card : hand) {
        delete card;
    }
}

void Player::discard() {
    Card* card1;
    Card* card2;
    hand.erase(std::find(hand.begin(), hand.end(), card1));
    hand.erase(std::find(hand.begin(), hand.end(), card2));
}

Card* Player::playCard() {
    if (hand.empty()) {
        return nullptr;
    }

    while (true) {
        std::cout << name << ", please enter the card you want to play in the format '{Rank} of {Suit}'.\n";
        std::string rankString, ofString, suitString;
        std::cin >> rankString >> ofString >> suitString;

        try {
            if (ofString != "of") {
                throw std::invalid_argument("Invalid format");
            }

            Rank rank = stringToRank(rankString);
            Suit suit = stringToSuit(suitString);

            auto it = std::find_if(hand.begin(), hand.end(), [rank, suit](Card* card) {
                return card->rank == rank && card->suit == suit;
                });

            if (it != hand.end()) {
                Card* card = *it;
                hand.erase(it);
                return card;
            }
            else {
                std::cout << "You don't have that card. Please choose another card.\n";
            }
        }
        catch (const std::invalid_argument& e) {
            std::cout << e.what() << ". Please enter a valid card in the format '{Rank} of {Suit}'.\n";
        }
    }
}

void Player::showCards() {
    std::cout << name << "'s cards: ";
    for (int i = 0; i < hand.size(); i++) {
        std::cout << rankToString(hand[i]->rank) << " of " << suitToString(hand[i]->suit);
        if (i < hand.size() - 1) {
            std::cout << ", ";
        }
        else {
            std::cout << ".";
        }
    }
    std::cout << std::endl;
}

void Player::revealCards() {
    std::cout << "Let's reveal " << name << "'s cards:\n";
    for (int i = 0; i < hand.size(); i++) {
        std::cout << rankToString(hand[i]->rank) << " of " << suitToString(hand[i]->suit);
        if (i < hand.size() - 1) {
            std::cout << ", ";
        }
        else {
            std::cout << ".";
        }
    }
    std::cout << std::endl;
}

TradeResult Player::makeBid(TradeResult highestBid, bool isFirstBid) {
    std::string bidString;
    TradeResult userBid = TradeResult::Passout;
    bool validBid = false;

    while (!validBid) {
        std::cout << name << ", please make your bid. The highest bid is " << tradeResultToString(highestBid) << ".\n";
        std::cin >> bidString;

        if (std::cin.eof()) {
            std::cin.clear();
            break;
        }

        if (bidString == "Pass") {
            userBid = TradeResult::Passout;
        }
        else if (bidString == "Misere") {
            userBid = TradeResult::Misere;
        }
        else if (bidString == "Miserewithouttalon") {
            userBid = TradeResult::MisereWithoutTalon;
        }
        else if (bidString == "Sixspades") {
            userBid = TradeResult::SixSpades;
        }
        else if (bidString == "Sixclubs") {
            userBid = TradeResult::SixClubs;
        }
        else if (bidString == "Sixdiamonds") {
            userBid = TradeResult::SixDiamonds;
        }
        else if (bidString == "Sixhearts") {
            userBid = TradeResult::SixHearts;
        }
        else if (bidString == "Sixnotrump") {
            userBid = TradeResult::SixNoTrump;
        }
        else if (bidString == "Sevenspades") {
            userBid = TradeResult::SevenSpades;
        }
        else if (bidString == "Sevenclubs") {
            userBid = TradeResult::SevenClubs;
        }
        else if (bidString == "Sevendiamonds") {
            userBid = TradeResult::SevenDiamonds;
        }
        else if (bidString == "Sevenhearts") {
            userBid = TradeResult::SevenHearts;
        }
        else if (bidString == "Sevennotrump") {
            userBid = TradeResult::SevenNoTrump;
        }
        else if (bidString == "Eightspades") {
            userBid = TradeResult::EightSpades;
        }
        else if (bidString == "Eightclubs") {
            userBid = TradeResult::EightClubs;
        }
        else if (bidString == "Eightdiamonds") {
            userBid = TradeResult::EightDiamonds;
        }
        else if (bidString == "Eighthearts") {
            userBid = TradeResult::EightHearts;
        }
        else if (bidString == "Eightnotrump") {
            userBid = TradeResult::EightNoTrump;
        }
        else if (bidString == "Ninespades") {
            userBid = TradeResult::NineSpades;
        }
        else if (bidString == "Nineclubs") {
            userBid = TradeResult::NineClubs;
        }
        else if (bidString == "Ninediamonds") {
            userBid = TradeResult::NineDiamonds;
        }
        else if (bidString == "Ninehearts") {
            userBid = TradeResult::NineHearts;
        }
        else if (bidString == "Ninenotrump") {
            userBid = TradeResult::NineNoTrump;
        }
        else if (bidString == "Tenspades") {
            userBid = TradeResult::TenSpades;
        }
        else if (bidString == "Tenclubs") {
            userBid = TradeResult::TenClubs;
        }
        else if (bidString == "Tendiamonds") {
            userBid = TradeResult::TenDiamonds;
        }
        else if (bidString == "Tenhearts") {
            userBid = TradeResult::TenHearts;
        }
        else if (bidString == "Tennotrump") {
            userBid = TradeResult::TenNoTrump;
        }
        else if (bidString == "Ninespadeswithouttalon") {
            userBid = TradeResult::NineSpadesWithoutTalon;
        }
        else if (bidString == "Ninenotrumpwithouttalon") {
            userBid = TradeResult::NineNoTrumpWithoutTalon;
        }
        else if (bidString == "Tenspadeswithouttalon") {
            userBid = TradeResult::TenSpadesWithoutTalon;
        }
        else if (bidString == "Tennotrumpwithouttalon") {
            userBid = TradeResult::TenNoTrumpWithoutTalon;
            std::cout << name << " has bid " << tradeResultToString(userBid) << "It's the highest bid possible.\n";
            return userBid;
        }

        if (userBid == TradeResult::Passout && bidString != "Pass") {
            std::cout << "Invalid bid. Please make another bid.\n";
            continue;
        }
        else if (userBid == TradeResult::Passout && bidString == "Pass") {
            std::cout << name << " has bid pass.\n";
            return userBid;
        }
        else if (static_cast<int>(userBid) < static_cast<int>(highestBid)) {
            std::cout << "You cannot make a bid lower than the highest bid. Please make another bid.\n";
        }
        else {
            validBid = true;
            bidNumber = tradeResultToBidNumber(userBid);
        }
    }

    std::cout << name << " has bid " << tradeResultToString(userBid) << ".\n";
    return userBid;
}


void Player::incrementTrickCount() {
    trickCount++;
}

void Player::awardPoints() {
    score += 1/*awardPointsForNoTricks*/;
}

void Player::penalizePoints(int trickCount) {
    score -= trickCount/* * penaltyPointsPerTrick*/;
}

void Player::resetTrickCount() {
    trickCount = 0;
}

int Player::getTrickCount() {
    return trickCount;
}

bool Player::decideWhist() {
    return true;
}

Card* Player::playCardInResponseTo(Suit leadSuit, Suit trumpSuit) {
    auto it = std::find_if(hand.begin(), hand.end(), [leadSuit](Card* card) {
        return card->suit == leadSuit;
        });

    if (it != hand.end()) {
        Card* card = *it;
        hand.erase(it);
        return card;
    }
    else {
        it = std::find_if(hand.begin(), hand.end(), [trumpSuit](Card* card) {
            return card->suit == trumpSuit;
            });

        if (it != hand.end()) {
            Card* card = *it;
            hand.erase(it);
            return card;
        }
        else {
            Card* card = hand.back();
            hand.pop_back();
            return card;
        }
    }
}

bool Player::hasSuit(Suit suit) {
    for (Card* card : hand) {
        if (card->suit == suit) {
            return true;
        }
    }
    return false;
}