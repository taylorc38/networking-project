#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>
#include <memory>
#include <iostream>
#include <thread>

class Server {
public:
     Server(unsigned short port);
     ~Server();
     void start();
private:
     unsigned short m_port;
     std::unique_ptr<sf::TcpSocket> m_socket;
     std::unique_ptr<sf::TcpListener> m_listener;
     std::unique_ptr<std::thread> m_waitForClientsThread;
     std::unique_ptr<std::thread> m_runThread;
     std::unique_ptr<std::thread> m_listenerThread;

     void waitForClients();
     void listen();
     void run();
     void pingClients();
};

#endif
