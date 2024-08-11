#pragma once
#include <SFML/Graphics.hpp>
#include "GameBoard.h"
class GameBoard;
class StartScreen {
public:
    StartScreen();
    void displayStartScreen(sf::RenderWindow& window);
    bool buttonPressed(sf::Vector2i& mousePosition, GameBoard& board);
private:
    sf::Text m_text;
    sf::Font m_font;
};