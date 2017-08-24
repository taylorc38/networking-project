#include "game.h"

Game::Game() {
     m_ip = "127.0.0.1";
     m_port = 50001;
}

Game::Game(const std::string ip, const unsigned short port) {
     m_ip = ip;
     m_port = port;
}

void Game::start() {
     m_client = std::make_unique<Client>(m_ip, m_port, this);
     m_client->start();
     run();
}

void Game::run() {
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

void Game::onPacketReceived(sf::Packet packet) {
     std::string strData;
     packet >> strData;
     std::cout << "Received packet through callback: " << strData << std::endl;
}
