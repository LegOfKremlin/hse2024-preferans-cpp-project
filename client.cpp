//#include <boost/asio.hpp>
//#include <iostream>
//#include <string>
//
//using boost::asio::ip::tcp;
//
//class Client {
//public:
//    Client(boost::asio::io_service& io_service, const std::string& host, const std::string& port)
//        : socket_(io_service) {
//        tcp::resolver resolver(io_service);
//        boost::asio::connect(socket_, resolver.resolve({ host, port }));
//    }
//
//    void send(const std::string& message) {
//        boost::asio::write(socket_, boost::asio::buffer(message + "\n"));
//    }
//
//    std::string receive() {
//        boost::asio::streambuf buf;
//        boost::asio::read_until(socket_, buf, "\n");
//        std::string data = boost::asio::buffer_cast<const char*>(buf.data());
//        return data.substr(0, data.size() - 1);  // Exclude newline
//    }
//
//private:
//    tcp::socket socket_;
//};
//
//int main() {
//    boost::asio::io_service io_service;
//    Client client(io_service, "localhost", "12345");
//
//    std::string input;
//    while (std::getline(std::cin, input)) {
//        client.send(input);
//        std::string response = client.receive();
//        std::cout << "Server response: " << response << std::endl;
//    }
//
//    return 0;
//}