#include "table.hpp"

using namespace godot;

void Table::_bind_methods() {
    //ClassDB::bind_method(D_METHOD("shuffleDeck"), &Table::shuffleDeck);
    //ClassDB::bind_method(D_METHOD("cutDeck"), &Table::cutDeck);
    //ClassDB::bind_method(D_METHOD("dealCards"), &Table::dealCards);
}

Table::Table() {}

Table::~Table() {}

void Table::_init() {
    currentPlayer = nullptr;
    dealer = nullptr;
}

//void Table::shuffleDeck() {
//    std::random_device rd;
//    std::mt19937 g(rd());
//    std::shuffle(deck.begin(), deck.end(), g);
//}
//
//void Table::cutDeck() {
//    std::rotate(deck.begin(), deck.begin() + deck.size() / 2, deck.end());
//}

//void Table::dealCards() {
//    for (int i = 0; i < players.size(); i++) {
//        Player* player = godot::Object::cast_to<Player>(players[i]);
//        if (player) {
//            player->hand.insert(player->hand.end(), deck.begin(), deck.begin() + 10);
//            deck.erase(deck.begin(), deck.begin() + 10);
//        }
//    }
//    talon.insert(talon.end(), deck.begin(), deck.end());
//    deck.clear();
//}