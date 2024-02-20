// ������� �������������, ����� ��� ������������ �������� � �������� ������ � Godot

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
    Pass, // ���
    Misere, // �����
    SixSpades, // 6 ���
    SixClubs, // 6 ����
    SixDiamonds, // 6 �����
    SixHearts, // 6 ������
    SixNoTrump, // 6 ��� ������
    SevenSpades, // 7 ���
    SevenClubs, // 7 ����
    SevenDiamonds, // 7 �����
    SevenHearts, // 7 ������
    SevenNoTrump, // 7 ��� ������
    EightSpades, // 8 ���
    EightClubs, // 8 ����
    EightDiamonds, // 8 �����
    EightHearts, // 8 ������
    EightNoTrump, // 8 ��� ������
    NineSpades, // 9 ���
    NineClubs, // 9 ����
    NineDiamonds, // 9 �����
    NineHearts, // 9 ������
    NineNoTrump, // 9 ��� ������
    TenSpades, // 10 ���
    TenClubs, // 10 ����
    TenDiamonds, // 10 �����
    TenHearts, // 10 ������
    TenNoTrump // 10 ��� ������
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
        // ������� ��������� ������� ����� �� ����
        hand.erase(std::remove(hand.begin(), hand.end(), card1), hand.end());
        hand.erase(std::remove(hand.begin(), hand.end(), card2), hand.end());
    }

    Bid bid(Bid highestBid, bool isFirstBid) {
        // ���� ��� ������ ������ � ����� ����� ������� ������ "�����", �� ������ ��
        if (isFirstBid && canBidMisere()) {
            return Bid::Misere;
        }

        // ���� ����� �� ����� ������� ������ ���� ������� ���������, �� ������� "���"
        if (!canBidHigher(highestBid)) {
            return Bid::Pass;
        }

        // ����� ����� ������ ������ ���� ������� ���������
        // ����� ������ ���� ������ ������ ������
        // ��������, �� ������ ���������� ��������� ������ ����� ������� ���������
        currentBid = getNextBid(highestBid); // ��������� �������� ��� ������ ������
        return currentBid;
    }

    Card playCard(Card card) {
        // ����� ������ ������
        hand.erase(std::remove(hand.begin(), hand.end(), card), hand.end());
        return card;
    }

    void openCards() {
        // ����� ������ ���� ������ �������� ����
    }

    bool outOfCards() {
        // ����� ������ ���� ������ ��������, ���� �� � ������ �����
        return hand.empty();
    }

    void makeMove() {
        // ����� ������ ���� ������ ���� ������
    }

    int countTricks() {
        // ����� ������ ���� ������ �������� ������
        return 0; // ��������� ��������
    }

    void lose() {
        // ����� ������ ���� ������ ���������
    }

    void win() {
        // ����� ������ ���� ������ ��������
    }

private:
    bool canBidMisere() {
        // ����� ������ ���� ������ ��������, ����� �� ����� ������� ������ "�����"
        // ��������, �� ������ ���������� true
        return true;
    }

    bool canBidHigher(Bid highestBid) {
        // ����� ������ ���� ������ ��������, ����� �� ����� ������� ������ ���� ������� ���������
        // ��������, �� ������ ���������� true
        return true;
    }

    Bid getNextBid(Bid highestBid) {
        // ����� ������ ���� ������ ������ ��������� ������ ����� ������� ���������
        // ��������, �� ������ ���������� ��������� ������
        return static_cast<Bid>(static_cast<int>(highestBid) + 1);
    }
};

class Table {
public:
    std::vector<Card> deck;
    std::vector<Card> playedCards;
    std::vector<Card> talon; // ������
    std::vector<Player> players;
    Player* currentPlayer;
    Player* dealer; // �������

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
    void handleRound();     // ��������� ������
    void handleWhist(); // ��������� �����
    void handlePass(); // ���
    void handleSettings(); // ���������
    void revealTalon(); // �������� ������
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
    void endGame(); // ���������� ���� 

    void handleMiserePlay(Player& player) {
        // ��� ������ ��������� ���� �����
        for (Player& p : players) {
            p.openCards();
        }

        // ������ ������ ����, ���� � ��� ���� �����
        while (!player.outOfCards()) {
            for (Player& p : players) {
                p.makeMove();
            }
        }

        // ������������ ���������� ������ � ������
        int tricksTaken = player.countTricks();

        // ���� ����� ���� ���� ���� ������, �� �����������
        if (tricksTaken > 0) {
            player.lose();
        }
        else {
            player.win();
        }
    }

    void handleRaspasyPlay() {
        // ��� ������ ��������� ���� �����
        for (Player& p : players) {
            p.openCards();
        }

        // ������ ������ ����, ���� � ��� ���� �����
        while (!players[0].outOfCards()) {
            for (Player& p : players) {
                p.makeMove();
            }
        }

        // ������������ ���������� ������ � ������� ������
        for (Player& p : players) {
            int tricksTaken = p.countTricks();
            // ���� ����� ���� ���� ���� ������, �� �����������
            if (tricksTaken > 0) {
                p.lose();
            }
            else {
                p.win();
            }
        }
    }

    void handleWhist() {
        // ����� ������ ���� ������ ��������� �����
        // ��������, �� ������ ������� ��������� � ������ �����
        std::cout << "���� �������.\n";
    }

    void handleGamePlay(); // ��������� ����
};