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

     m_waitForClientsThread->detach();
     m_runThread->detach();

     while (true) {}
}

void Server::waitForClients() {
     while (true) {
          auto client = std::make_unique<sf::TcpSocket>();
          if (m_listener->accept(*client) != sf::Socket::Done) {
               std::printf("Error accepting client\n");
          } else {
               m_socket = std::move(client);
               std::printf("Client connected to server\n");
          }
     }
}

void Server::run() {
     sf::Clock clock;
     while(true) {
        sf::Time elapsed = clock.getElapsedTime();
        if (elapsed.asSeconds() >= 3) {
             std::printf("Pinging clients\n");
             pingClients();
             clock.restart();
        }
    }
}

void Server::pingClients() {
     sf::Packet packet;
     packet << "Hello world";
     if (m_socket->send(packet) != sf::Socket::Done) {
          std::printf("Error sending packet\n");
     }
}
