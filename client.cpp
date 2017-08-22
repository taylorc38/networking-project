#include "client.h"

Client::Client(std::string ip, unsigned short port) {
     m_ip = ip;
     m_port = port;
     m_socket = std::make_unique<sf::TcpSocket>();
}

void Client::start() {
     std::string statusStr = "Attempting to connect to server...";
     sf::Socket::Status status;
     status = m_socket->connect(m_ip, m_port);
     if (status != sf::Socket::Done) {
          std::cout << "Error connecting to server" << std::endl;
     }
     std::cout << "Connected to server. Starting thread to listen for data..." << std::endl;

     m_listenerThread = std::make_unique<std::thread>([=] { listen(); });
     m_listenerThread->detach();

     std::cout << "Starting game loop" << std::endl;
     run();
}

// Listen for data from the server
void Client::listen() {
     std::cout << "Listening for packets..." << std::endl;
     sf::Packet packet;
     std::string strData;
     while (true) {
          if (m_socket->receive(packet) != sf::Socket::Done) {
               // std::printf("Error receiving packet");
               continue;
          }
          packet >> strData;
          std::cout << strData << std::endl;
          packet.clear();
     }
}

// Game loop
void Client::run() {
     // do stuff with window
     sf::ContextSettings settings;
     settings.antialiasingLevel = 8;
     sf::RenderWindow window(sf::VideoMode(800, 600), "ClientServerProject", sf::Style::Default, settings);

     while (window.isOpen()) {
          // Check all the window's events that were triggered since the last iteration of the loop
         sf::Event event;
         while (window.pollEvent(event)) {
              // Run the event through relevant systems
              switch (event.type) {
                   case sf::Event::KeyPressed:
                         if (event.key.code == sf::Keyboard::Key::A) {
                              if (m_socket) {
                                   std::cout << "A pressed - Pinging server" << std::endl;
                                   pingServer();
                              }
                         }
                   break;
                   case sf::Event::Closed:
                         window.close();
                   break;
              }
         }
         // Clear the window with black color
         window.clear(sf::Color::Black);
         // draw things here
         // end the current frame to display the things we just drew
         window.display();
    }
}

void Client::pingServer() {
     sf::Packet packet;
     packet << "Hello server";
     if (m_socket->send(packet) != sf::Socket::Done) {
          // error
     }
}
