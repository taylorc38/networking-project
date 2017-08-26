#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>
#include <memory>
#include <iostream>
#include <thread>
#include <vector>

#include "clientEntity.h"

class Server {
public:
     Server(unsigned short port);
     ~Server();
     void start();
private:
     unsigned short m_port;
     unsigned short m_currId;
     std::vector<ClientEntity> m_clients;

     std::unique_ptr<sf::TcpListener> m_listener;
     std::unique_ptr<std::thread> m_waitForClientsThread;

     void waitForClients();
     void listen(int);
     void run();
     void clientHandshake(int, int);
     void pingClients();
};

#endif
