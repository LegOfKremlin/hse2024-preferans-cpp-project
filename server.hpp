#ifndef GAME_SERVER_HPP_
#define GAME_SERVER_HPP_

#include <vector>
#include <algorithm>
#include <random>
#include <boost/asio/ip/tcp.hpp>

#include "table.hpp"
#include "player.hpp"

class GameServer {
public:
    Table* table;
    std::vector<Player*> players;

    GameServer();
    ~GameServer();

    void startGame();
    void handleRound();
    void handleBidding();
    void handleRaspasyPlay();
    void handleMiserePlay(Player* player);
    Player* determineRoundWinner();
    void handleWhist();
    void handlePass();
    void handleSettings();
    void revealTalon();
    void endGame();
    void handleGamePlay();
    void handlePlayerAction(Player* player, Card* card);
    Player* determineBidWinner();
};

#endif // GAME_SERVER_HPP_