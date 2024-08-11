#pragma once
class Tile {
public:
    Tile(float size);
public:
    void setPosition(float a, float b);
    void draw(sf::RenderWindow& window) const;
    sf::Vector2f getTilePosition() const;
    int getTileXPosition() const;
    bool isEmpty();
    void setColor(sf::Color& color);
    sf::Color getColor();
private:
    sf::CircleShape m_shape;
    sf::RectangleShape m_tile;
    void centerCircle();
};