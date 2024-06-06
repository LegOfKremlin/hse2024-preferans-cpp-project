//#include "server.hpp"
//#include <iostream>
//#include <set>
//#include <string>
//#include <memory>
//
//using boost::asio::ip::tcp;
//
//Session::Session(tcp::socket socket, Player* player, Table* table)
//    : socket_(std::move(socket)), player_(player), table_(table) {
//}
//
//void Session::start() {
//    do_ask_name();
//}
//
//void Session::do_ask_name() {
//    auto self(shared_from_this());
//    std::string ask_name_msg = "Please enter your name: ";
//    boost::asio::async_write(socket_, boost::asio::buffer(ask_name_msg),
//        [this, self](boost::system::error_code ec, std::size_t length) {
//            if (!ec) {
//                do_read_name();
//            }
//        });
//}
//
//void Session::do_read_name() {
//    auto self(shared_from_this());
//    boost::asio::async_read_until(socket_, buffer_, '\n',
//        [this, self](boost::system::error_code ec, std::size_t length) {
//            if (!ec) {
//                std::istream stream(&buffer_);
//                std::string line;
//                std::getline(stream, line);
//                player_->name = line;
//                do_read();
//            }
//        });
//}
//
//void Session::do_read() {
//    auto self(shared_from_this());
//    boost::asio::async_read_until(socket_, buffer_, '\n',
//        [this, self](boost::system::error_code ec, std::size_t length) {
//            if (!ec) {
//                std::istream stream(&buffer_);
//                std::string line;
//                std::getline(stream, line);
//                // Handle the line of input from the client.
//                std::string response = player_->handleCommand(line);
//                do_write(response);
//            }
//        });
//}
//
//void Session::do_write(const std::string& message) {
//    auto self(shared_from_this());
//    boost::asio::async_write(socket_, boost::asio::buffer(message),
//        [this, self](boost::system::error_code ec, std::size_t length) {
//            if (!ec) {
//                do_read();
//            }
//        });
//}
//
//GameServer::GameServer(boost::asio::io_service& io_service, short port)
//    : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
//    socket_(io_service) {
//    do_accept();
//    startNewGame();
//}
//
//GameServer::~GameServer() {
//    delete table;
//    for (auto player : players) {
//        delete player;
//    }
//}
//
//void GameServer::startNewGame() {
//    table->startNewRound();
//
//    std::cout << "Dealer: " << table->dealer->name << std::endl;
//    std::cout << "First move goes to: " << table->currentPlayer->name << std::endl;
//
//    table->shuffleDeck();
//    table->dealCards();
//    table->showTalon();
//
//    for (auto player : table->players) {
//        player->showCards();
//    }
//
//    int tradeResult = table->handleTrade();
//
//    switch (tradeResult) {
//    case static_cast<int>(TradeResult::Passout):
//        std::cout << "All players passed. Playing Raspass.\n";
//        table->handleRaspasyPlay();
//        break;
//    case static_cast<int>(TradeResult::Misere):
//        std::cout << "Misere declared. Playing Misere.\n";
//        table->handleMiserePlay(table->getCurrentPlayer());
//        break;
//    default:
//        std::cout << "Playing Whist.\n";
//        table->handleWhistPlay(table->getCurrentPlayer());
//        break;
//    }
//}
//
//void GameServer::do_accept() {
//    acceptor_.async_accept(socket_,
//        [this](boost::system::error_code ec) {
//            if (!ec) {
//                if (players.size() < 3) {
//                    Player* player = new Player();
//                    players.push_back(player);
//                    table->addPlayer(player);
//
//                    std::make_shared<Session>(std::move(socket_), player, table)->start();
//
//                    if (players.size() == 3) {
//                        startNewGame();
//                    }
//                }
//                else {
//                    socket_.close();
//                }
//            }
//
//            do_accept();
//        });
//}
//
//int main() {
//    try {
//        boost::asio::io_service io_service;
//
//        GameServer server(io_service, 12345);
//
//        io_service.run();
//    }
//    catch (std::exception& e) {
//        std::cerr << "Exception: " << e.what() << "\n";
//    }
//
//    return 0;
//}