#ifndef CLIENT_CALLBACK_INTERFACE_H
#define CLIENT_CALLBACK_INTERFACE_H

#include <string>

class ClientCallbackInterface {
public:
     virtual void onPacketReceived(std::string) = 0;
};

#endif
