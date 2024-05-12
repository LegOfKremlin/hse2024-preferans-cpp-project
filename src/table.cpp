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

void Table::startNewRound() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> distr(0, 2);

    dealerIndex = distr(g);

    dealer = players[dealerIndex % players.size()];
    currentPlayer = players[(dealerIndex + 1) % players.size()];
   /* playedCards.clear();
    talon.clear();
    shuffleDeck();
    cutDeck();
    dealerIndex++;
    dealCards();*/
}

void Table::handleCardPlayed(Card* card) {
    auto it = std::find(currentPlayer->hand.begin(), currentPlayer->hand.end(), card);
    if (it != currentPlayer->hand.end()) {
        currentPlayer->hand.erase(it);
        playedCards.push_back(card);
        //next player
        int currentPlayerIndex = std::find(players.begin(), players.end(), currentPlayer) - players.begin();
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
            if (passCount == players.size() - 1) {
                trade_end = true;
                result = static_cast<int>(TradeResult::Passout);
            }
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
            break;
        }

        if (static_cast<int>(bid) > static_cast<int>(highestBid)) {
            highestBid = bid;
        }

        if (trade_end) {
            if (lastSignificantMove == Move::Bidding) {
                trumpSuit = lastPlayerMadeSignificantMove->getBidSuit();
            }
            return result;
        }
    }
    return static_cast<int>(TradeResult::SevenSpades); // default return
}

void Table::handleRaspasyPlay() {
//    for (int i = 0; i < 10; i++) {
//        for (Player* player : players) {
//            Card card = player->playCard();
//        }
//
//        Player* trickWinner = determineTrickWinner();
//    }
//
//    for (Player* player : players) {
//        bool tookTrick = checkIfPlayerTookTrick(player);
//        if (!tookTrick) {
//            player->awardPoints();
//        }
//        else {
//            player->penalizePoints();
//        }
//    }
}

void Table::handleMiserePlay(Player* player) {
    TradeResult game = TradeResult::Misere;

    player->revealCards();

    /*for (int i = 0; i < 10; i++) {
        for (Player* player : players) {
            Card* card = player->playCard();
        }

        Player* trickWinner = determineTrickWinner();
    }

    bool contractFulfilled = checkContractFulfillment(player);
    if (contractFulfilled) {
    }
    else {
    }*/
}

void Table::handleWhistPlay(Player* player) {
    for (Card* card : talon) {
        //show talon
    }

    player->discard();

    TradeResult game = static_cast<TradeResult>(handleTrade());

    for (Player* otherPlayer : players) {
        if (otherPlayer != player) {
            bool whist = otherPlayer->decideWhist();
            if (whist) {
            }
            else {
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        for (Player* player : players) {
            Card* card = player->playCard();
        }

        Player* trickWinner = determineTrickWinner();
    }

    bool contractFulfilled = checkContractFulfillment(player);
    if (contractFulfilled) {

    }
    else {

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
        // If a trump card is played and it's higher than the current highest card
        else if (playedCards[i]->suit == trumpSuit && (highestCard->suit != trumpSuit || playedCards[i]->rank > highestCard->rank)) {
            highestCard = playedCards[i];
            trickWinner = players[i];
        }
    }

    // Clear the played cards for the next trick
    playedCards.clear();

    return trickWinner;
}

bool Table::checkContractFulfillment(Player* player) {

    return false;
}
