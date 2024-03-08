#ifndef GAME_SERVER_HPP_
#define GAME_SERVER_HPP_

#include <vector>
#include <algorithm>
#include <random>

#include "table.hpp"
//#include "player.hpp"

namespace godot{

class GameServer : public Node {
    
    GDCLASS(GameServer, Node);

public:
    Table* table;
    godot::Array players;

    static void _bind_methods();

    //void _process(double delta) override;

    GameServer();
    ~GameServer();

    void _init();

    //void startGame();
    //void handleRound();
    //void handleBidding();
    //void handleRaspasyPlay();
    //void handleMiserePlay(Player* player);
    //Player* determineRoundWinner();
    //void handleWhist();
    //void handlePass();
    //void handleSettings();
    //void revealTalon();
    //void endGame();
    //void handleGamePlay();
    //void handlePlayerAction(Player* player, Card card);
    //Player* determineBidWinner();
};

} // namespace godot
#endif // GAME_SERVER_HPP_