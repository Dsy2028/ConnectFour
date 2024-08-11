#pragma once

#include <SFML/Graphics.hpp>

class Button {
public:
    Button(std::string string, sf::Vector2f position, float size);
    void draw(sf::RenderWindow& window);
private:
    sf::Text m_text;
    sf::Font m_font;
    sf::RectangleShape m_shape;
    void centerText();
};