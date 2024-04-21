#include "server.hpp"
#include "player.hpp"
#include "table.hpp"
#include "card.hpp"

#include <iostream>

class ConsoleGame {
public:
    void startGame() {
        GameServer server;
        Table table;
        server.table = &table;

        // Добавляем игроков
        for (int i = 0; i < 4; i++) {
            Player* player = new Player();
            table.addPlayer(player);
        }

        // Запускаем игру
        table.startNewRound();

        // Основной игровой цикл
        while (true) {
            // Обрабатываем ходы игроков
            for (Player* player : table.players) {
                Card* card = player->playCard();
                table.handleCardPlayed(card);
            }

            // Проверяем, закончилась ли игра
            if (gameOver()) {
                break;
            }
        }

        // Определяем победителя
        Player* winner = determineWinner();
        std::cout << "Winner is: " << winner->name << std::endl;
    }

    bool gameOver() {
        // Здесь должна быть логика определения окончания игры
        return false;
    }

    Player* determineWinner() {
        // Здесь должна быть логика определения победителя
        return nullptr;
    }
};

int main() {
    ConsoleGame game;
    game.startGame();
    return 0;
}