#include "server.h"

// TODO instead of storing sf::TcpSockets in m_clients, store a struct with client metadata as well as the pointer

Server::Server(unsigned short port) {
     m_port = port;
     m_listener = std::make_unique<sf::TcpListener>();
     m_clients = std::vector<std::unique_ptr<sf::TcpSocket>>();
}

Server::~Server() {
     m_listener.reset();
     m_waitForClientsThread.reset();
}

void Server::start() {
     std::cout << "Server starting..." << std::endl;
     if (m_listener->listen(m_port) != sf::Socket::Done) {
          std::cout << "Error listening to port " << m_port << std::endl;
          return;
     }

     m_waitForClientsThread = std::make_unique<std::thread>([=] { waitForClients(); });
     m_waitForClientsThread->detach();

     run();
}

void Server::waitForClients() {
     while (true) {
          auto p_client = std::make_unique<sf::TcpSocket>();
          if (m_listener->accept(*p_client) != sf::Socket::Done) {
               std::cout << "Error accepting client" << std::endl;
          } else {
               std::cout << "Client connected to server" << std::endl;
               m_clients.push_back(std::move(p_client));
               // Each connected client should have its own listen thread
               std::thread listenerThread([=] { listen(m_clients.size() - 1); });
               listenerThread.detach();
          }
     }
}

void Server::listen(int clientIndex) {
     sf::Packet packet;
     std::string strData;
     while (true) {
          if (m_clients[clientIndex]->receive(packet) != sf::Socket::Done) {
               continue;
          }
          packet >> strData;
          std::cout << "data received from client: " << strData << std::endl;
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

     for (int i = 0; i < m_clients.size(); i++) {
          if (m_clients[i]->send(packet) != sf::Socket::Done) {
               std::cout << "Error sending packet to client" << std::endl;
          }
     }
}
