#ifndef CLIENT_H
#define CLIENT_H

#include "clientCallbackInterface.h"
#include <SFML/Network.hpp>
#include <memory>
#include <thread>
#include <iostream>

class Client {
public:
     Client(std::string, unsigned short port);
     void start();
private:
     std::string m_ip;
     unsigned short m_port;
     std::unique_ptr<sf::TcpSocket> m_socket;
     std::unique_ptr<std::thread> m_listenerThread;
     std::unique_ptr<ClientCallbackInterface> m_clientCallbackInterface;

     void listen();
     void pingServer();
};

#endif
