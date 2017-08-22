#ifndef GAME_H
#define GAME_H

#include "client.h"

class Game {
public:
     Game();
     Game(const std::string, const unsigned short);
     void start();
private:
     std::string m_ip;
     unsigned short m_port;
     std::unique_ptr<Client> m_client;

     void run();
};

#endif
