#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Player {
public:
    Player(float size);
    void changePlayerColor();
    void draw(sf::RenderWindow& window) const;
    void setPosition(float column);
    sf::Color getColor();
    std::string getColorAsString();
private:
    sf::CircleShape m_shape;
};