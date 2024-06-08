#include <iostream>
#include <sstream>

#include "table.hpp"

Table::Table() : currentPlayer(nullptr), dealer(nullptr), trumpSuit(Suit::Hearts) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> distr(0, 2);

    dealerIndex = distr(g);

    for (int suit = 0; suit < 4; suit++) {
        for (int rank = 0; rank < 8; rank++) {
            Card* card = new Card();
            card->suit = static_cast<Suit>(suit);
            card->rank = static_cast<Rank>(rank);
            deck.push_back(card);
        }
    }
}

Table::~Table() {
    for (auto card : deck) {
        delete card;
    }
    for (auto card : playedCards) {
        delete card;
    }
    for (auto card : talon) {
        delete card;
    }
    for (auto player : players) {
        delete player;
    }
}

void Table::shuffleDeck() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
}

void Table::addPlayer(Player* player) {
    players.push_back(player);
}

void Table::cutDeck() {
    std::rotate(deck.begin(), deck.begin() + deck.size() / 2, deck.end());
}

void Table::dealCards() {
    for (int i = 0; i < players.size(); i++) {
        Player* player = players[i];
        player->hand.insert(player->hand.end(), deck.begin(), deck.begin() + 10);
        deck.erase(deck.begin(), deck.begin() + 10);
    }
    talon.insert(talon.end(), deck.begin(), deck.end());
    deck.clear();
}

void Table::showTalon() {
    std::cout << "Talon cards: ";
    for (int i = 0; i < talon.size(); i++) {
        std::cout << rankToString(talon[i]->rank) << " of " << suitToString(talon[i]->suit);
        if (i < talon.size() - 1) {
            std::cout << ", ";
        }
        else {
            std::cout << ".";
        }
    }
    std::cout << std::endl;
}

void Table::startNewRound() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> distr(0, 2);

    size_t dealerIndex = static_cast<size_t>(distr(g));

    dealer = players[dealerIndex % players.size()];
    currentPlayer = players[(dealerIndex + 1) % players.size()];
}

void Table::handleCardPlayed(Card* card) {
    auto it = std::find(currentPlayer->hand.begin(), currentPlayer->hand.end(), card);
    if (it != currentPlayer->hand.end()) {
        currentPlayer->hand.erase(it);
        playedCards.push_back(card);
        int currentPlayerIndex = static_cast<int>(std::find(players.begin(), players.end(), currentPlayer) - players.begin());
        currentPlayer = players[(currentPlayerIndex + 1) % players.size()];
    }
    else {
        // exception ??
    }
}

int Table::handleTrade() {
    bool trade_end = false;
    int result;
    Move lastSignificantMove = Move::Passout;
    Player* lastPlayerMadeSignificantMove = nullptr;
    int passCount = 0;
    TradeResult highestBid = TradeResult::Passout;

    for (int i = 1; i < players.size(); i = (i + 1) % players.size()) {
        int playerIndex = (std::find(players.begin(), players.end(), dealer) - players.begin() + i) % players.size();
        currentPlayer = players[playerIndex];
        TradeResult bid = currentPlayer->makeBid(highestBid, i == 1);

        switch (bid) {
        case TradeResult::Passout:
            passCount++;
            //if (passCount == 3) {
            //    trade_end = true;
            //    result = static_cast<int>(TradeResult::Passout);
            //}
            break;
        case TradeResult::Misere:
            if (highestBid == TradeResult::Passout) {
                highestBid = bid;
                lastPlayerMadeSignificantMove = currentPlayer;
                trade_end = true;
                result = static_cast<int>(TradeResult::Misere);
            }
            break;
        default:
            if (static_cast<int>(bid) > static_cast<int>(highestBid)) {
                highestBid = bid;
                lastPlayerMadeSignificantMove = currentPlayer;
            }
            passCount = 0;
            break;
        }

        if (passCount == 3) {
            return static_cast<int>(TradeResult::Passout);
        }

        if (passCount == players.size() - 1 && highestBid != TradeResult::Passout) {
            return static_cast<int>(highestBid);
        }

        //if (static_cast<int>(bid) > static_cast<int>(highestBid)) {
        //    highestBid = bid;
        //}

        //if (trade_end) {
        //    if (lastSignificantMove == Move::Bidding) {
        //        trumpSuit = lastPlayerMadeSignificantMove->getBidSuit();
        //    }

        //    return result;
        //}
    }
    //return static_cast<int>(TradeResult::SevenSpades); // default return
    return static_cast<int>(highestBid);
}

void Table::handleRaspasyPlay() {
    for (int i = 0; i < 10; i++) {
        for (Player* player : players) {
            std::cout << player->name << ", it's your turn to play a card.\n";
            Card* card = player->playCard();
            playedCards.push_back(card);
            std::cout << player->name << " played " << card->toString() << ".\n";
        }

        Player* trickWinner = determineTrickWinner();
        trickWinner->incrementTrickCount();
        std::cout << trickWinner->name << " won the trick.\n";
    }

    for (Player* player : players) {
        int trickCount = player->getTrickCount();
        if (trickCount == 0) {
            std::cout << player->name << " didn't take any tricks and gets a bonus!\n";
            player->awardPoints();
        }
        else {
            std::cout << player->name << " took " << trickCount << " tricks and gets penalized.\n";
            player->penalizePoints(trickCount);
        }
        player->resetTrickCount();
    }
}

void Table::handleMiserePlay(Player* player) {
    TradeResult game = TradeResult::Misere;

    player->revealCards();

    //for (int i = 0; i < 10; i++) {
    //    for (Player* player : players) {
    //        Card* card = player->playCard();
    //    }

    //    Player* trickWinner = determineTrickWinner();
    //}

    //bool contractFulfilled = checkContractFulfillment(player);
    //if (contractFulfilled) {
    //}
    //else {
    //}
}

void Table::handleWhistPlay(Player* dealer) {
    size_t dealerIndex = std::find(players.begin(), players.end(), dealer) - players.begin();
    Suit leadSuit;

    for (int round = 0; round < 10; round++) {
        for (size_t i = 1; i <= players.size(); i++) {
            currentPlayer = players[(dealerIndex + i) % players.size()];

            if (currentPlayer->hand.empty()) {
                std::cout << currentPlayer->name << " has no cards left to play.\n";
                continue;
            }

            Card* card;
            bool validCard = false;
            while (!validCard) {
                std::cout << currentPlayer->name << ", please enter the card you want to play in the format '{Rank} of {Suit}'.\n";
                std::string rankString, ofString, suitString;
                std::cin >> rankString >> ofString >> suitString;

                if (std::cin.eof()) {
                    std::cout << "EOF detected, exiting program.\n";
                    exit(0);
                }

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


                if (rankString.empty() || ofString.empty() || suitString.empty()) {
                    continue;
                }

                if (ofString != "of") {
                    std::cout << "Invalid card input. Please enter a valid card in the format '{Rank} of {Suit}'.\n";
                    continue;
                }

                Rank rank = stringToRank(rankString);
                Suit suit = stringToSuit(suitString);

                auto it = std::find_if(currentPlayer->hand.begin(), currentPlayer->hand.end(), [rank, suit](Card* card) {
                    return card->rank == rank && card->suit == suit;
                    });

                if (it == currentPlayer->hand.end()) {
                    std::cout << "You don't have that card. Please choose another card.\n";
                    continue;
                }

                if (!playedCards.empty() && (*it)->suit != playedCards[0]->suit && currentPlayer->hasSuit(playedCards[0]->suit)) {
                    std::cout << "You must follow the suit of the first card played. Please choose another card.\n";
                    continue;
                }

                card = *it;
                currentPlayer->hand.erase(it);
                validCard = true;
            }

            playedCards.push_back(card);
            std::cout << currentPlayer->name << " played " << rankToString(card->rank) << " of " << suitToString(card->suit) << std::endl;
        }

        Player* trickWinner = determineTrickWinner();
        trickWinner->incrementTrickCount();
        std::cout << trickWinner->name << " won the trick.\n";

        dealerIndex = std::find(players.begin(), players.end(), trickWinner) - players.begin();
        playedCards.clear();
    }

    for (Player* player : players) {
        int trickCount = player->getTrickCount();
        int requiredTricks = getRequiredTricksForWhist(dealer->getBidNumber());
        if (trickCount >= requiredTricks) {
            std::cout << player->name << " fulfilled the contract.\n";
            player->awardPoints();
        }
        else {
            std::cout << player->name << " did not fulfill the contract.\n";
            player->penalizePoints(requiredTricks - trickCount);
        }
        player->resetTrickCount();
    }
}

Player* Table::determineTrickWinner() {
    Card* leadingCard = playedCards[0];
    Card* highestCard = leadingCard;
    Player* trickWinner = players[0];

    for (int i = 1; i < playedCards.size(); i++) {
        if (playedCards[i]->suit == leadingCard->suit && playedCards[i]->rank > highestCard->rank) {
            highestCard = playedCards[i];
            trickWinner = players[i];
        }
        else if (playedCards[i]->suit == trumpSuit && highestCard->suit != trumpSuit) {
            highestCard = playedCards[i];
            trickWinner = players[i];
        }
    }

    playedCards.clear();

    return trickWinner;
}

bool Table::checkContractFulfillment(Player* player) {

    return false;
}

int Table::getRequiredTricksForWhist(int bidNumber) {
    switch (bidNumber) {
    case 6:
        return 4;
    case 7:
        return 2;
    case 8:
    case 9:
        return 1;
    case 10:
        return 0;
    default:
        return 0;
    }
}