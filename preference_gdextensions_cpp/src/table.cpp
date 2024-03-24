#include "table.hpp"


using namespace godot;

void Table::_bind_methods() {
    ClassDB::bind_method(D_METHOD("shuffleDeck"), &Table::shuffleDeck);
    ClassDB::bind_method(D_METHOD("cutDeck"), &Table::cutDeck);
    ClassDB::bind_method(D_METHOD("addPlayer"), &Table::addPlayer);
    ClassDB::bind_method(D_METHOD("startNewRound"), &Table::startNewRound);
    ClassDB::bind_method(D_METHOD("handleTrade"), &Table::handleTrade);
    ClassDB::bind_method(D_METHOD("handleCardPlayed"), &Table::handleCardPlayed);
    ClassDB::bind_method(D_METHOD("handleRaspasyPlay"), &Table::handleRaspasyPlay);
    ClassDB::bind_method(D_METHOD("handleMiserePlay"), &Table::handleMiserePlay);
    ClassDB::bind_method(D_METHOD("handleWhistPlay"), &Table::handleWhistPlay);
    ClassDB::bind_method(D_METHOD("dealCards"), &Table::dealCards);
}

Table::Table() {}

Table::~Table() {}

void Table::_init() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> distr(0, 2);

    dealerIndex = distr(g);
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
        Player* player = godot::Object::cast_to<Player>(players[i]);
        if (player) {
            player->hand.insert(player->hand.end(), deck.begin(), deck.begin() + 10);
            deck.erase(deck.begin(), deck.begin() + 10);
        }
    }
    talon.insert(talon.end(), deck.begin(), deck.end());
    deck.clear();
}

void Table::startNewRound() {

    dealer = godot::Object::cast_to<Player>(players[dealerIndex % players.size()]);
    currentPlayer = godot::Object::cast_to<Player>(players[(dealerIndex + 1) % players.size()]);
    playedCards.clear();
    talon.clear();
    shuffleDeck();
    cutDeck();
    dealerIndex++;
    dealCards();
}

void Table::handleCardPlayed(Card* card) {
    auto it = std::find(currentPlayer->hand.begin(), currentPlayer->hand.end(), card);
    if (it != currentPlayer->hand.end()) {
        currentPlayer->hand.erase(it);
        playedCards.push_back(card);
        //next player
        currentPlayer = players[std::find(players.begin(), players.end(), currentPlayer) - players.begin() + 1];
    }
    else {
        // exception ??
    }
}

int Table::handleTrade() {
    bool trade_end = false;
    int result;
    
    for (int i = 1; i < players.size(); i = (i + 1) % players.size()) {
        int playerIndex = (std::find(players.begin(), players.end(), dealer) - players.begin() + i) % players.size();
        currentPlayer = godot::Object::cast_to<Player>(players[playerIndex]);
        Move move = static_cast<Move>(currentPlayer->makeMove());

        switch (move) {
        case Move::Bidding:
            result = static_cast<int>(TradeResult::SevenSpades);
            break;
        case Move::Passout:
            result = static_cast<int>(TradeResult::Passout);
            break;
        case Move::Misere:
            result = static_cast<int>(TradeResult::Misere);
            break;
        }
        //case Move::Bidding:
        //    if (move > lastSignificantMove) {
        //        lastSignificantMove = move;
        //        lastPlayerMadeSignificantMove = currentPlayer;
        //    }
        //    break;
        //case Move::Passout:
        //    passCount++;
        //    break;
        //case Move::Misere:
        //    if (lastSignificantMove == Move::Passout) {
        //        lastSignificantMove = move;
        //        lastPlayerMadeSignificantMove = currentPlayer;
        //    }
        //    break;
        //}

        if (trade_end) {
			return result;
		}
    }
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

    return nullptr;
}

bool Table::checkContractFulfillment(Player* player) {

    return false;
}
