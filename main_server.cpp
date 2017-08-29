#include <iostream>
#include <signal.h>
#include "server.h"

void signalHandler(int s) {
     std::cout << "Caught signal: " << s << std::endl;
     std::exit(0);
}

int main(int argc, char* argv[]) {
     std::cout << "main_server.cpp :: This is the first line of code!" << std::endl;

     struct sigaction sigIntHandler;
     sigIntHandler.sa_handler = signalHandler;
     sigemptyset(&sigIntHandler.sa_mask);
     sigIntHandler.sa_flags = 0;

     sigaction(SIGINT, &sigIntHandler, NULL);

     const unsigned short PORT = 50001;
     Server server(PORT);
     server.start();

     return 0;
}
