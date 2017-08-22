#include "server.h"

Server::Server(unsigned short port) {
     m_port = port;
     m_listener = std::make_unique<sf::TcpListener>();
     m_socket = std::make_unique<sf::TcpSocket>();
}

Server::~Server() {
     m_listener.reset();
     m_socket.reset();
     m_waitForClientsThread.reset();
     m_runThread.reset();
}

void Server::start() {
     std::cout << "Server starting..." << std::endl;
     if (m_listener->listen(m_port) != sf::Socket::Done) {
          std::cout << "Error listening to port " << m_port << std::endl;
          return;
     }
     std::cout << "Creating and detaching threads" << std::endl;

     m_waitForClientsThread = std::make_unique<std::thread>([=] { waitForClients(); });
     m_runThread = std::make_unique<std::thread>([=] { run(); });
     m_listenerThread = std::make_unique<std::thread>([=] { listen(); });

     m_waitForClientsThread->detach();
     m_runThread->detach();
     m_listenerThread->detach();

     while (true) {}
}

void Server::waitForClients() {
     while (true) {
          auto client = std::make_unique<sf::TcpSocket>();
          if (m_listener->accept(*client) != sf::Socket::Done) {
               std::cout << "Error accepting client" << std::endl;
          } else {
               m_socket = std::move(client);
               std::cout << "Client connected to server" << std::endl;
          }
     }
}

void Server::listen() {
     std::cout << "Listening for packets..." << std::endl;
     sf::Packet packet;
     std::string strData;
     while (true) {
          if (m_socket->receive(packet) != sf::Socket::Done) {
               // std::cout << "Error receiving packet" << std::endl;
               continue;
          }
          packet >> strData;
          std::cout << strData << std::endl;
          packet.clear();
     }
}

void Server::run() {
     sf::Clock clock;
     while(true) {
        sf::Time elapsed = clock.getElapsedTime();
        if (elapsed.asSeconds() >= 3) {
             std::cout << "Pinging clients" << std::endl;
             pingClients();
             clock.restart();
        }
    }
}

void Server::pingClients() {
     sf::Packet packet;
     packet << "Hello client";
     if (m_socket->send(packet) != sf::Socket::Done) {
          std::cout << "Error sending packet" << std::endl;
     }
}
