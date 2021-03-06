#ifndef CLIENT_H
#define CLIENT_H

#include "clientCallbackInterface.h"

#include <SFML/Network.hpp>
#include <memory>
#include <thread>
#include <iostream>

class Client {
public:
     Client(std::string, unsigned short port, ClientCallbackInterface*);
     ~Client();
     void start();
     void setId(int id) { m_id = id; }

private:
     std::string m_ip;
     unsigned short m_port;
     bool m_isRunning;
     int m_id;
     std::unique_ptr<sf::TcpSocket> m_socket;
     std::unique_ptr<std::thread> m_listenerThread;
     ClientCallbackInterface *m_callbackTarget;

     void listen();
     void pingServer();
};

#endif
