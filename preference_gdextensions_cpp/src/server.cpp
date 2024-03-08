#include "server.hpp"

using namespace godot;

void GameServer::_bind_methods() {
    //ClassDB::bind_method(D_METHOD("startGame"), &GameServer::startGame);
    //ClassDB::bind_method(D_METHOD("handleRound"), &GameServer::handleRound);
    //ClassDB::bind_method(D_METHOD("handleBidding"), &GameServer::handleBidding);
    //ClassDB::bind_method(D_METHOD("handleRaspasyPlay"), &GameServer::handleRaspasyPlay);
    //ClassDB::bind_method(D_METHOD("handleMiserePlay", "player"), &GameServer::handleMiserePlay);
    //ClassDB::bind_method(D_METHOD("determineRoundWinner"), &GameServer::determineRoundWinner);
    //ClassDB::bind_method(D_METHOD("handleWhist"), &GameServer::handleWhist);
    //ClassDB::bind_method(D_METHOD("handlePass"), &GameServer::handlePass);
    //ClassDB::bind_method(D_METHOD("handleSettings"), &GameServer::handleSettings);
    //ClassDB::bind_method(D_METHOD("revealTalon"), &GameServer::revealTalon);
    //ClassDB::bind_method(D_METHOD("endGame"), &GameServer::endGame);
    //ClassDB::bind_method(D_METHOD("handleGamePlay"), &GameServer::handleGamePlay);
    //ClassDB::bind_method(D_METHOD("handlePlayerAction", "player", "card"), &GameServer::handlePlayerAction);
    //ClassDB::bind_method(D_METHOD("determineBidWinner"), &GameServer::determineBidWinner);
}

GameServer::GameServer() {}

GameServer::~GameServer() {}

void GameServer::_init() {
    table = nullptr;
}