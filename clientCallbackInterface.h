#ifndef CLIENT_CALLBACK_INTERFACE_H
#define CLIENT_CALLBACK_INTERFACE_H

#include <SFML/Network.hpp>

class ClientCallbackInterface {
public:
     virtual void onPacketReceived(sf::Packet) {
          throw "onPacketReceived not implemented";
     }
};

#endif
