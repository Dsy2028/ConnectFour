#include "Player.h"
#include <SFML/Graphics.hpp>



    Player::Player(float size) {
        m_shape.setFillColor(sf::Color::Red);
        m_shape.setRadius(size / 2.15f);
        m_shape.setPosition(95, 10);
    }

    void Player::changePlayerColor() {
        m_shape.getFillColor() == sf::Color::Red ? m_shape.setFillColor(sf::Color::Yellow) : m_shape.setFillColor(sf::Color::Red);
    }
    void Player::draw(sf::RenderWindow& window) const {
        window.draw(m_shape);
    }
    void Player::setPosition(float column) {
        m_shape.setPosition(column - 5, m_shape.getPosition().y);
    }
    sf::Color Player::getColor() {
        return m_shape.getFillColor();
    }
    std::string Player::getColorAsString() {
        return m_shape.getFillColor() == sf::Color::Red ? "Red" : "Yellow";
    }
