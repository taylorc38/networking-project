#include <iostream>
#include <memory>

#include "server.h"
#include "client.h"

int main(int argc, char *argv[]) {
     std::cout << "Networking Project - this is the first line of code!" << std::endl;
     if (argc < 2) {
          std::cout << "Please supply an argument" << std::endl;
          return 0;
     }
     auto port = 50012;

     std::string arg(argv[1]);
     if (arg == "server") {
          // start server
          Server server(port);
          server.start();
     } else if (arg == "client") {
          // start client
          Client client("127.0.0.1", port);
          client.start();
     } else {
          std::cout << "Accepted arguments: server, client. Aborting!" << std::endl;
     }
     return 0;
}
