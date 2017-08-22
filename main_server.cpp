#include <iostream>
#include "server.h"

int main(int argc, char* argv[]) {
     std::cout << "main_server.cpp :: This is the first line of code!" << std::endl;

     const unsigned short PORT = 50001;
     Server server(PORT);
     server.start();

     return 0;
}
