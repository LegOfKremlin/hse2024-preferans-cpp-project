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

void Player::revealCards() {
    std::cout << "Let's reveal " << name << "'s cards:\n";
    for (auto card : hand) {
        std::cout << rankToString(card->rank) << " of " << suitToString(card->suit) << ", ";
    }
    std::cout << std::endl;
}

void Player::showCards() {
    std::cout << name << "'s cards: ";
    for (auto card : hand) {
        std::cout << rankToString(card->rank) << " of " << suitToString(card->suit) << ", ";
    }
    std::cout << std::endl;
}

//TODO: refactor this monster
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

        if (userBid == TradeResult::Passout && bidString != "pass") {
            std::cout << "Invalid bid. Please make another bid.\n";
            continue;
        }

        if (static_cast<int>(userBid) < static_cast<int>(highestBid)) {
            std::cout << "You cannot make a bid lower than the highest bid. Please make another bid.\n";
        }
        else {
            validBid = true;
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
    //would player whist?
    return true;
}

Suit Player::getBidSuit() const {
    return Suit::Hearts;
}
