#include "server.hpp"

GameServer::GameServer() {
    table = nullptr;
}

GameServer::~GameServer() {
    delete table;
    for (auto player : players) {
        delete player;
    }
}