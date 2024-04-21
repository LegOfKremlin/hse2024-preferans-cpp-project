#include "player.hpp"
#include <iostream>
#include <string>

Player::Player() {}

Player::~Player() {
    for (auto card : hand) {
        delete card;
    }
}

void Player::discard() {
    //choice should be given
    Card* card1;
    Card* card2;
    hand.erase(std::find(hand.begin(), hand.end(), card1));
    hand.erase(std::find(hand.begin(), hand.end(), card2));
}

Card* Player::playCard() {
    // For now, we just return the first card in the hand
    if (!hand.empty()) {
        Card* card = hand.front();
        hand.erase(hand.begin());
        return card;
    }
    return nullptr;
}

void Player::revealCards() {

}

//TODO: refactor this monster
TradeResult Player::makeBid(TradeResult highestBid, bool isFirstBid) {
    std::string bidString;
    std::cin >> bidString;
    TradeResult userBid = TradeResult::Passout;


    if (bidString == "pass") {
        userBid = TradeResult::Passout;
    }
    else if (bidString == "misere") {
        userBid = TradeResult::Misere;
    }
    else if (bidString == "miserewithouttalon") {
        userBid = TradeResult::MisereWithoutTalon;
    }
    else if (bidString == "sixspades") {
        userBid = TradeResult::SixSpades;
    }
    else if (bidString == "sixclubs") {
        userBid = TradeResult::SixClubs;
    }
    else if (bidString == "sixdiamonds") {
        userBid = TradeResult::SixDiamonds;
    }
    else if (bidString == "sixhearts") {
        userBid = TradeResult::SixHearts;
    }
    else if (bidString == "sixnotrump") {
        userBid = TradeResult::SixNoTrump;
    }
    else if (bidString == "sevenspades") {
        userBid = TradeResult::SevenSpades;
    }
    else if (bidString == "sevenclubs") {
        userBid = TradeResult::SevenClubs;
    }
    else if (bidString == "sevendiamonds") {
        userBid = TradeResult::SevenDiamonds;
    }
    else if (bidString == "sevenhearts") {
        userBid = TradeResult::SevenHearts;
    }
    else if (bidString == "sevennotrump") {
        userBid = TradeResult::SevenNoTrump;
    }
    else if (bidString == "eightspades") {
        userBid = TradeResult::EightSpades;
    }
    else if (bidString == "eightclubs") {
        userBid = TradeResult::EightClubs;
    }
    else if (bidString == "eightdiamonds") {
        userBid = TradeResult::EightDiamonds;
    }
    else if (bidString == "eighthearts") {
        userBid = TradeResult::EightHearts;
    }
    else if (bidString == "eightnotrump") {
        userBid = TradeResult::EightNoTrump;
    }
    else if (bidString == "ninespades") {
        userBid = TradeResult::NineSpades;
    }
    else if (bidString == "nineclubs") {
        userBid = TradeResult::NineClubs;
    }
    else if (bidString == "ninediamonds") {
        userBid = TradeResult::NineDiamonds;
    }
    else if (bidString == "ninehearts") {
        userBid = TradeResult::NineHearts;
    }
    else if (bidString == "ninenotrump") {
        userBid = TradeResult::NineNoTrump;
    }
    else if (bidString == "tenspades") {
        userBid = TradeResult::TenSpades;
    }
    else if (bidString == "tenclubs") {
        userBid = TradeResult::TenClubs;
    }
    else if (bidString == "tendiamonds") {
        userBid = TradeResult::TenDiamonds;
    }
    else if (bidString == "tenhearts") {
        userBid = TradeResult::TenHearts;
    }
    else if (bidString == "tennotrump") {
        userBid = TradeResult::TenNoTrump;
    }
    else if (bidString == "ninespadeswithouttalon") {
        userBid = TradeResult::NineSpadesWithoutTalon;
    }
    else if (bidString == "ninenotrumpwithouttalon") {
        userBid = TradeResult::NineNoTrumpWithoutTalon;
    }
    else if (bidString == "tenspadeswithouttalon") {
        userBid = TradeResult::TenSpadesWithoutTalon;
    }
    else if (bidString == "tennotrumpwithouttalon") {
        userBid = TradeResult::TenNoTrumpWithoutTalon;
    }
    else {
        // invalid bid
    }

    if (static_cast<int>(userBid) < static_cast<int>(highestBid)) {
        std::cout << "You cannot make a bid lower than the highest bid. Please make another bid.\n";
        return makeBid(highestBid, isFirstBid);
    }

    return userBid;
}

//int Player::makeMove() {
//    return static_cast<int>(Move::Passout);
//}

bool Player::decideWhist() {
    //would player whist?
    return true;
}

Suit Player::getBidSuit() const {
    return Suit::Hearts;
}