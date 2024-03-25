#include "player.hpp"
#include "typing.hpp"

using namespace godot;

void Player::_bind_methods() {
    ClassDB::bind_method(D_METHOD("discard"), &Player::discard);
    //ClassDB::bind_method(D_METHOD("bid"), &Player::bid);
    ClassDB::bind_method(D_METHOD("playCard"), &Player::playCard);
    //ClassDB::bind_method(D_METHOD("openCards"), &Player::openCards);
    //ClassDB::bind_method(D_METHOD("outOfCards"), &Player::outOfCards);
    ClassDB::bind_method(D_METHOD("makeMove"), &Player::makeMove);
    //ClassDB::bind_method(D_METHOD("incrementScore"), &Player::incrementScore);
    //ClassDB::bind_method(D_METHOD("countTricks"), &Player::countTricks);
    //ClassDB::bind_method(D_METHOD("lose"), &Player::lose);
    //ClassDB::bind_method(D_METHOD("win"), &Player::win);
}

void Player::discard() {
    //choice should be given
    Card* card1;
    Card* card2;
    hand.erase(std::find(hand.begin(), hand.end(), card1));
    hand.erase(std::find(hand.begin(), hand.end(), card2));
}

Card* Player::playCard() {
    //choice should be given
    Card* chosenCard = nullptr;

    return chosenCard;
}

void Player::revealCards() {

}

int Player::makeMove() {
    return static_cast<int>(Move::Passout);
}

bool Player::decideWhist() {
    //would player whist?
	return true;
}

Player::Player() {}

Player::~Player() {}

void Player::_init() {

}
