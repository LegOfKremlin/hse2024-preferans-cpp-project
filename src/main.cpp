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
                if (std::cin.eof()) {
					std::cin.clear();
                    name = "noname";
                }
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

        int tradeResult = table->handleTrade();

        switch (tradeResult) {
        case static_cast<int>(TradeResult::Passout):
            std::cout << "All players passed. Playing Raspass.\n";
            table->handleRaspasyPlay();
            break;
        case static_cast<int>(TradeResult::Misere):
            std::cout << "Misere declared. Playing Misere.\n";
            table->handleMiserePlay(table->getCurrentPlayer());
            break;
        default:
            std::cout << "Playing Whist.\n";
            table->handleWhistPlay(table->getCurrentPlayer());
            break;
        }
    }
};

int main() {
    ConsoleGame game;
    game.startNewGame();
    return 0;
}
