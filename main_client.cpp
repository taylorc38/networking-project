#include <iostream>
#include <string>
#include "game.h"

int main(int argc, char* argv[]) {
     std::cout << "main_client.cpp :: This is the first line of code!" << std::endl;

     const std::string IP = "127.0.0.1";
     const unsigned short PORT = 50001;
     Game game(IP, PORT);
     game.start();

     return 0;
}
