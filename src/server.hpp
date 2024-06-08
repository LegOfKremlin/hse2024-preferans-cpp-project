//#ifndef SERVER_HPP_
//#define SERVER_HPP_
//
//#include <boost/asio.hpp>
//#include "table.hpp"
//#include "player.hpp"
//
//using boost::asio::ip::tcp;
//
//class Session : public std::enable_shared_from_this<Session> {
//public:
//    Session(tcp::socket socket, Player* player, Table* table);
//
//    void start();
//
//private:
//    void do_read();
//    void do_write(const std::string& message);
//
//    tcp::socket socket_;
//    boost::asio::streambuf buffer_;
//    Player* player_;
//    Table* table_;
//};
//
//class GameServer {
//public:
//    
//    GameServer(boost::asio::io_service& io_service, short port);
//    ~GameServer();
//    void startNewGame();
//
//private:
//    void do_accept();
//
//    tcp::acceptor acceptor_;
//    tcp::socket socket_;
//    Table* table;
//    std::vector<Player*> players;
//};
//
//#endif // SERVER_HPP_