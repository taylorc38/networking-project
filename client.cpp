#include "client.h"

Client::Client(std::string ip, unsigned short port, ClientCallbackInterface *p_callbackTarget) {
     m_ip = ip;
     m_port = port;
     m_callbackTarget = p_callbackTarget;
     m_isRunning = true;
}

Client::~Client() {
     m_isRunning = false;
     m_callbackTarget = 0;
     m_socket.reset();
}

void Client::start() {
     m_socket = std::make_unique<sf::TcpSocket>();
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
               continue;
          }
          if (m_callbackTarget != 0) {
               m_callbackTarget->onPacketReceived(packet);
          }
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
