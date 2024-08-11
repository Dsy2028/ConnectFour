#include <SFML/Graphics.hpp>
#include "Button.h"


Button::Button(std::string string, sf::Vector2f position, float size) {
        m_shape.setSize(sf::Vector2f(size * 2, size));
        m_shape.setFillColor(sf::Color::Blue);
        m_shape.setPosition(position.x, position.y);
        m_font.loadFromFile("ClearSans-Regular.ttf");
        m_text.setCharacterSize(20);
        m_text.setFont(m_font);
        m_text.setString(string);
        centerText();
 }
    void Button::draw(sf::RenderWindow& window) {
        window.draw(m_shape);
        window.draw(m_text);
    }
    void Button::centerText() {
        sf::FloatRect textRect{ m_text.getLocalBounds() };
        m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        m_text.setPosition(m_shape.getPosition().x + m_shape.getSize().x / 2.0f, m_shape.getPosition().y + m_shape.getSize().y / 2.0f);
    }
