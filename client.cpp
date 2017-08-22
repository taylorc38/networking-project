#include "client.h"

Client::Client(std::string ip, unsigned short port) {
     m_ip = ip;
     m_port = port;
     m_socket = std::make_unique<sf::TcpSocket>();
}

void Client::start() {
     std::string statusStr = "Attempting to connect to server...";
     sf::Socket::Status status;
     status = m_socket->connect(m_ip, m_port);
     if (status != sf::Socket::Done) {
          std::cout << "Error connecting to server" << std::endl;
     }
     std::cout << "Connected to server. Starting thread to listen for data..." << std::endl;

     m_listenerThread = std::make_unique<std::thread>([=] { listen(); });
     m_listenerThread->detach();
}

// Listen for data from the server
void Client::listen() {
     std::cout << "Listening for packets..." << std::endl;
     sf::Packet packet;
     std::string strData;
     while (true) {
          if (m_socket->receive(packet) != sf::Socket::Done) {
               // std::printf("Error receiving packet");
               continue;
          }
          packet >> strData;
          std::cout << strData << std::endl;
          packet.clear();
     }
}

void Client::pingServer() {
     sf::Packet packet;
     packet << "Hello server";
     if (m_socket->send(packet) != sf::Socket::Done) {
          // error
     }
}
