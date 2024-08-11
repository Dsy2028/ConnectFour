#include <SFML/Graphics.hpp>
#include "Tile.h"

    Tile::Tile(float size) {
        m_tile.setSize(sf::Vector2f(size, size));
        m_tile.setFillColor(sf::Color::Blue);
        m_shape.setRadius(size / 2.15f);
        m_shape.setFillColor(sf::Color::White);

    }

    void Tile::setPosition(float a, float b) {
        m_tile.setPosition(a, b);
        centerCircle();
    }
    void Tile::draw(sf::RenderWindow& window) const {
        window.draw(m_tile);
        window.draw(m_shape);
    }
    sf::Vector2f Tile::getTilePosition() const {
        return m_tile.getPosition();
    }
    int Tile::getTileXPosition() const {
        return m_tile.getPosition().x;
    }
    bool Tile::isEmpty() {
        return m_shape.getFillColor() == sf::Color::White;
    }
    void Tile::setColor(sf::Color& color) {
        m_shape.setFillColor(color);
    }
    sf::Color Tile::getColor() {
        return m_shape.getFillColor();
    }
    void Tile::centerCircle() {
        sf::FloatRect shapeRect{ m_tile.getLocalBounds() };
        m_shape.setOrigin(shapeRect.left + shapeRect.width / 2.0f, shapeRect.top + shapeRect.height / 2.0f);
        m_shape.setPosition(m_tile.getPosition().x + m_tile.getSize().x / 2.0f, m_tile.getPosition().y + m_tile.getSize().y / 2.0f);
    }
