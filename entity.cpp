#include "entity.h"

Entity::Entity() {
     mIdentifier = DEFAULT_IDENTIFIER;
     mPosition = Position();
     mDimensions = Dimensions();
     mGraphics = Graphics();
}

Entity::Entity(const std::string identifier, const Position *pos, const Dimensions *dimensions, const Graphics *graphics) {
     mIdentifier = identifier;
     mPosition = *pos;
     mDimensions = *dimensions;
     mGraphics = *graphics;
}

Entity::~Entity() {

}

// Should be called each time we draw the Entity.
void Entity::updateDrawable() {
     mGraphics.rect.setSize(sf::Vector2f(mDimensions.width, mDimensions.height));
     mGraphics.rect.setPosition(mPosition.x, mPosition.y);
     mGraphics.rect.setFillColor(mGraphics.color);
}

sf::RectangleShape Entity::getDrawable() {
     updateDrawable();
     return mGraphics.rect;
}

void Entity::setPosition(int x, int y) {
     mPosition.x = x;
     mPosition.y = y;
}

std::string Entity::toString() {
     return mIdentifier + '\n' + mPosition.toString() + '\n' + mDimensions.toString() + '\n' + mGraphics.toString();
}
