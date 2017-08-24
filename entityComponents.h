#ifndef ENTITY_COMPONENTS_H
#define ENTITY_COMPONENTS_H

#include <SFML/Graphics.hpp>

struct Position {
     int x;
     int y;
     double velocityX;
     double velocityY;
     Position() : x(0), y(0), velocityX(0.0), velocityY(0.0) {}
     Position(const int x, const int y, const int velocityX, const int velocityY) {
          this->x = x;
          this->y = y;
          this->velocityX = velocityX;
          this->velocityY = velocityY;
     }
     Position operator= (const Position &other) {
          this->x = other.x;
          this->y = other.y;
          this->velocityX = other.velocityX;
          this->velocityY = other.velocityY;
     }
     std::string toString() {
          return "Position: " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(velocityX) + ", " + std::to_string(velocityY);
     }
};

struct Dimensions {
     int width;
     int height;
     int z;
     Dimensions() : width(100), height(100), z(1) {};
     Dimensions(const int width, const int height, const int z) {
          this->width = width;
          this->height = height;
          this->z = z;
     }
     Dimensions operator= (const Dimensions &other) {
          this->width = other.width;
          this->height = other.height;
          this->z = other.z;
     }
     std::string toString() {
          return "Dimensions: " + std::to_string(width) + ", " + std::to_string(height) + ", " + std::to_string(z);
     }
};

struct Graphics {
     sf::Color color; // For now just store a color.
     sf::RectangleShape rect;
     Graphics() : color(sf::Color::White), rect(sf::RectangleShape(sf::Vector2f(100, 100))) {};
     Graphics(sf::Color color, sf::RectangleShape rect) {
          this->color = color;
          this->rect = rect;
     }
     Graphics operator= (const Graphics &other) {
          this->color = other.color;
          this->rect = other.rect;
     }
     std::string toString() {
          return "Graphics: \nColor: (" + std::to_string(this->color.r) + ", " + std::to_string(this->color.g) + ", " + std::to_string(this->color.b) + ")";
     }
};

#endif
