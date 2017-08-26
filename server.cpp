#include "server.h"

Server::Server(unsigned short port) {
     m_port = port;
     m_currId = 1;
     m_listener = std::make_unique<sf::TcpListener>();
     m_clients = std::vector<ClientEntity>();
}

Server::~Server() {
     m_listener.reset();
     m_waitForClientsThread.reset();
}

void Server::start() {
     if (m_listener->listen(m_port) != sf::Socket::Done) {
          std::cout << "Error listening to port " << m_port << std::endl;
          return;
     }

     m_waitForClientsThread = std::make_unique<std::thread>([=] { waitForClients(); });
     m_waitForClientsThread->detach();

     run();
}

void Server::waitForClients() {
     std::cout << "Waiting for clients..." << std::endl;
     while (true) {
          auto p_client = std::make_unique<sf::TcpSocket>();
          if (m_listener->accept(*p_client) != sf::Socket::Done) {
               std::cout << "Error accepting client" << std::endl;
          } else {
               std::cout << "Client connected to server: client id " << m_currId << std::endl;
               ClientEntity client(m_currId, &p_client);
               m_currId++;
               m_clients.push_back(std::move(client));
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
          if (m_clients[clientIndex].clientSocket->receive(packet) != sf::Socket::Done) {
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
          if (m_clients[i].clientSocket->send(packet) != sf::Socket::Done) {
               std::cout << "Error sending packet to client" << std::endl;
          }
     }
}
