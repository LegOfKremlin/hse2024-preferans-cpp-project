// наивная имлпементация, нужна для последующего переноса в реальный проект в Godot

#include <vector>
#include <iostream>
#include <string>
#include <random>

enum class Suit { Hearts, Diamonds, Clubs, Spades };
enum class Rank { Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };

struct Card {
    Suit suit;
    Rank rank;
};

enum class Bid {
    Pass, // Пас
    Misere, // Мизер
    SixSpades, // 6 пик
    SixClubs, // 6 треф
    SixDiamonds, // 6 бубен
    SixHearts, // 6 червей
    SixNoTrump, // 6 без козыря
    SevenSpades, // 7 пик
    SevenClubs, // 7 треф
    SevenDiamonds, // 7 бубен
    SevenHearts, // 7 червей
    SevenNoTrump, // 7 без козыря
    EightSpades, // 8 пик
    EightClubs, // 8 треф
    EightDiamonds, // 8 бубен
    EightHearts, // 8 червей
    EightNoTrump, // 8 без козыря
    NineSpades, // 9 пик
    NineClubs, // 9 треф
    NineDiamonds, // 9 бубен
    NineHearts, // 9 червей
    NineNoTrump, // 9 без козыря
    TenSpades, // 10 пик
    TenClubs, // 10 треф
    TenDiamonds, // 10 бубен
    TenHearts, // 10 червей
    TenNoTrump // 10 без козыря
};

class Player {
public:
    std::string name;
    int score;
    int bullet;
    int mountain;
    int whist;
    std::vector<Card> hand;
    Bid currentBid;

    Player(std::string name) : name(name), score(0), bullet(0), mountain(0), whist(0) {}

    void discard(Card card1, Card card2) {
        // Удаляем выбранные игроком карты из руки
        hand.erase(std::remove(hand.begin(), hand.end(), card1), hand.end());
        hand.erase(std::remove(hand.begin(), hand.end(), card2), hand.end());
    }

    Bid bid(Bid highestBid, bool isFirstBid) {
        // Если это первая ставка и игрок может сделать ставку "Мизер", он делает ее
        if (isFirstBid && canBidMisere()) {
            return Bid::Misere;
        }

        // Если игрок не может сделать ставку выше текущей наивысшей, он говорит "Пас"
        if (!canBidHigher(highestBid)) {
            return Bid::Pass;
        }

        // Иначе игрок делает ставку выше текущей наивысшей
        // Здесь должна быть логика выбора ставки
        // Например, мы просто возвращаем следующую ставку после текущей наивысшей
        currentBid = getNextBid(highestBid); // обновляем свойство при каждой ставке
        return currentBid;
    }

    Card playCard(Card card) {
        // Игрок играет картой
        hand.erase(std::remove(hand.begin(), hand.end(), card), hand.end());
        return card;
    }

    void openCards() {
        // Здесь должна быть логика открытия карт
    }

    bool outOfCards() {
        // Здесь должна быть логика проверки, есть ли у игрока карты
        return hand.empty();
    }

    void makeMove() {
        // Здесь должна быть логика хода игрока
    }

    int countTricks() {
        // Здесь должна быть логика подсчета взяток
        return 0; // временное значение
    }

    void lose() {
        // Здесь должна быть логика проигрыша
    }

    void win() {
        // Здесь должна быть логика выигрыша
    }

private:
    bool canBidMisere() {
        // Здесь должна быть логика проверки, может ли игрок сделать ставку "Мизер"
        // Например, мы просто возвращаем true
        return true;
    }

    bool canBidHigher(Bid highestBid) {
        // Здесь должна быть логика проверки, может ли игрок сделать ставку выше текущей наивысшей
        // Например, мы просто возвращаем true
        return true;
    }

    Bid getNextBid(Bid highestBid) {
        // Здесь должна быть логика выбора следующей ставки после текущей наивысшей
        // Например, мы просто возвращаем следующую ставку
        return static_cast<Bid>(static_cast<int>(highestBid) + 1);
    }
};

class Table {
public:
    std::vector<Card> deck;
    std::vector<Card> playedCards;
    std::vector<Card> talon; // прикуп
    std::vector<Player> players;
    Player* currentPlayer;
    Player* dealer; // сдающий

    Table() : currentPlayer(nullptr), dealer(nullptr) {}

    void shuffleDeck() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(deck.begin(), deck.end(), g);
    }

    void cutDeck() {
        std::rotate(deck.begin(), deck.begin() + deck.size() / 2, deck.end());
    }

    void dealCards() {
        for (Player& player : players) {
            player.hand.insert(player.hand.end(), deck.begin(), deck.begin() + 10);
            deck.erase(deck.begin(), deck.begin() + 10);
        }
        talon.insert(talon.end(), deck.begin(), deck.end());
        deck.clear();
    }
    void handleRound();     // обработка раунда
    void handleWhist(); // обработка виста
    void handlePass(); // пас
    void handleSettings(); // настройки
    void revealTalon(); // показать прикуп
};

class GameServer {
public:
    Table table;
    std::vector<Player> players;

    void startGame() {
        table.shuffleDeck();
        table.cutDeck();
        table.dealCards();
        handleBidding();
    }

    void handlePlayerAction(Player& player, Card card) {
        player.playCard(card);
        table.playedCards.push_back(card);
    }
    void handleBidding() {
        Bid highestBid = Bid::Pass;
        Player* highestBidder = nullptr;
        bool isFirstBid = true;

        while (true) {
            for (Player& player : players) {
                Bid bid = player.bid(highestBid, isFirstBid);
                if (bid == Bid::Pass) {
                    continue;
                }

                if (bid == Bid::Misere) {
                    highestBid = bid;
                    highestBidder = &player;
                    break;
                }

                if (static_cast<int>(bid) > static_cast<int>(highestBid)) {
                    highestBid = bid;
                    highestBidder = &player;
                }

                isFirstBid = false;
            }

            if (highestBid == Bid::Misere || std::all_of(players.begin(), players.end(), [](Player& player) { return player.currentBid == Bid::Pass; })) {
                break;
            }
        }

        if (highestBid == Bid::Pass) {
            handleRaspasyPlay();
        }
        else if (highestBid == Bid::Misere) {
            handleMiserePlay(*highestBidder);
        }
        else {
            handleGamePlay();
        }
    }
    void endGame(); // завершение игры 

    void handleMiserePlay(Player& player) {
        // Все игроки открывают свои карты
        for (Player& p : players) {
            p.openCards();
        }

        // Игроки делают ходы, пока у них есть карты
        while (!player.outOfCards()) {
            for (Player& p : players) {
                p.makeMove();
            }
        }

        // Подсчитываем количество взяток у игрока
        int tricksTaken = player.countTricks();

        // Если игрок взял хоть одну взятку, он проигрывает
        if (tricksTaken > 0) {
            player.lose();
        }
        else {
            player.win();
        }
    }

    void handleRaspasyPlay() {
        // Все игроки открывают свои карты
        for (Player& p : players) {
            p.openCards();
        }

        // Игроки делают ходы, пока у них есть карты
        while (!players[0].outOfCards()) {
            for (Player& p : players) {
                p.makeMove();
            }
        }

        // Подсчитываем количество взяток у каждого игрока
        for (Player& p : players) {
            int tricksTaken = p.countTricks();
            // Если игрок взял хоть одну взятку, он проигрывает
            if (tricksTaken > 0) {
                p.lose();
            }
            else {
                p.win();
            }
        }
    }

    void handleWhist() {
        // Здесь должна быть логика обработки виста
        // Например, мы просто выводим сообщение о начале виста
        std::cout << "Вист начался.\n";
    }

    void handleGamePlay(); // обработка игры
};
