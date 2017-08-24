#ifndef GAME_H
#define GAME_H

#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "client.h"
#include "clientCallbackInterface.h"

class Game : public ClientCallbackInterface {
public:
     Game();
     Game(const std::string, const unsigned short);
     void start();
     void onPacketReceived(sf::Packet);
private:
     std::string m_ip;
     unsigned short m_port;
     std::unique_ptr<Client> m_client;

     void run();
};

#endif
