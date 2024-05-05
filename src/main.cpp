#include <iostream>
#include <set>
#include <string>

#include "server.hpp"
#include "player.hpp"
#include "table.hpp"
#include "card.hpp"

class ConsoleGame {
public:
    void startNewGame() {
        GameServer server;
        Table* table = new Table();
        server.table = table;

        std::set<std::string> names;
        for (int i = 0; i < 3; i++) {
            std::string name;
            do {
                std::cout << "Please, enter the name of player " << i + 1 << ": ";
                std::cin >> name;
            } while (names.find(name) != names.end());
            names.insert(name);

            Player* player = new Player();
            player->name = name;
            table->addPlayer(player);
        }

        table->startNewRound();

        std::cout << "Dealer: " << table->dealer->name << std::endl;
        std::cout << "First move goes to: " << table->currentPlayer->name << std::endl;

		table->shuffleDeck();
        table->dealCards();

        for (auto player : table->players) {
            player->showCards();
        }

        TradeResult bid = table->players[0]->makeBid(TradeResult::Passout, true);
        std::cout << "First player bid: " << tradeResultToString(bid) << std::endl;
    }
};

int main() {
    ConsoleGame game;
    game.startNewGame();
    return 0;
}
