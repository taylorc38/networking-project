#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "log.h"
#include "entityComponents.h" // includes Position, Dimensions, and Graphics components

/*
     Entities are the actors of the game - they should hold a state that can be modified by systems.
     Entity data should be stored in components (e.g. Position).
*/

class Entity {
public:
     Entity();
     Entity(const std::string, const Position *, const Dimensions *, const Graphics *);
     ~Entity();
     void updateDrawable();
     sf::RectangleShape getDrawable();
     void setPosition(int, int);
     std::string toString();
protected:
     std::string mIdentifier;
     Position mPosition;
     Dimensions mDimensions;
     Graphics mGraphics;
private:
     const std::string DEFAULT_IDENTIFIER = "Entity";
};

#endif
