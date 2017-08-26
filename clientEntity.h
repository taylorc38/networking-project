#ifndef CLIENT_ENTITY_H
#define CLIENT_ENTITY_H

#include <SFML/Network.hpp>
#include <memory>

struct ClientEntity {
public:
     ClientEntity(int _id, std::unique_ptr<sf::TcpSocket> *socket) : id(_id), clientSocket(std::move(*socket)) {}
     ClientEntity(ClientEntity&& other) : id(other.id), clientSocket(std::move(other.clientSocket)) {}

     std::unique_ptr<sf::TcpSocket> clientSocket;
     unsigned short id;
};

#endif
