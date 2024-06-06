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

        // ��������� �������
        for (int i = 0; i < 4; i++) {
            Player* player = new Player();
            table.addPlayer(player);
        }

        // ��������� ����
        table.startNewRound();

        // �������� ������� ����
        while (true) {
            // ������������ ���� �������
            for (Player* player : table.players) {
                Card* card = player->playCard();
                table.handleCardPlayed(card);
            }

            // ���������, ����������� �� ����
            if (gameOver()) {
                break;
            }
        }

        // ���������� ����������
        Player* winner = determineWinner();
        std::cout << "Winner is: " << winner->name << std::endl;
    }

    bool gameOver() {
        // ����� ������ ���� ������ ����������� ��������� ����
        return false;
    }

    Player* determineWinner() {
        // ����� ������ ���� ������ ����������� ����������
        return nullptr;
    }
};

int main() {
    ConsoleGame game;
    game.startGame();
    return 0;
}