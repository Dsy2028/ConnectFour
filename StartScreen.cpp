#include "StartScreen.h"
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameType.h"
StartScreen::StartScreen() {
    m_font.loadFromFile("ClearSans-Regular.ttf");
    m_text.setFont(m_font);
    m_text.setCharacterSize(100);
    m_text.setString("Connect 4");
    m_text.setPosition(100, 10);
    m_text.setFillColor(sf::Color::Blue);
}

void StartScreen::displayStartScreen(sf::RenderWindow& window) {
    Button button1{ "Player against AI", sf::Vector2f(100, 200),100.f };
    Button button2{ "Player against Player", sf::Vector2f(400, 200),100.f };
    window.clear(sf::Color::White);
    window.draw(m_text);
    button1.draw(window);
    button2.draw(window);
}
bool StartScreen::buttonPressed(sf::Vector2i& mousePosition, GameBoard& board) {
    if (mousePosition.x >= 100 && mousePosition.x <= 300 && mousePosition.y >= 200 && mousePosition.y <= 300) {
        board.setMatchType(gameType::ai);
        return true;
    }
    else if (mousePosition.x >= 400 && mousePosition.x <= 600 && mousePosition.y >= 200 && mousePosition.y <= 300) {
        std::cout << "second button pressed." << '\n';
        board.setMatchType(gameType::player);
        return true;
    }
    return false;
}