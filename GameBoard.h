#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "StartScreen.h"
#include "Tile.h"
#include "Player.h"
#include "GameType.h"

class GameBoard{
public:
    GameBoard();
public:
    void run();
    bool isMouseWithinBoard();
    void setMatchType(const gameType type);
    void printPositions();
   

 private:
     sf::Vector2i m_mousePosition;
     const int m_rows{ 6 };
     const int m_cols{ 7 };
     const float m_rectSize{ 85.f };
     const float m_topBottomSpacing{ 100.f };
     const float m_leftSpacing{ 100.f };
     bool endGame{};
     bool m_gameType{false};
     sf::Text m_text;
     sf::Text m_otherText;
     sf::Font m_font;
     std::vector<std::vector<Tile>> m_board;
     const std::vector<int> columnPositions{100,185,270,355,440,525,610,};
      std::map<int, int> m_map{ {100,0},{185,1},{270,2},{355,3},{440,4},{525,5},{610,6} };
     Player player{m_rectSize};
     sf::Color aiColor = sf::Color::Yellow;
     void initBoard();
     void drawBoard(sf::RenderWindow& window);
     int closestPosition();
     bool isColumnValid(int col);

     void placePiece(int col, sf::Color color);
     void movePlayerToMouse(bool mouseWithinBoard);
     void placePlayer(sf::Event& event, int closestPosition);
     void aiMove();
     bool checkWin(int col, int row, sf::Color& color);
     bool checkDiagonal(int col, int row, sf::Color& color);

     bool checkDiagonalDirection(int col, int row, sf::Color& color, int colStep, int rowStep);
     int findFirstEmptyRow(int col);
     void displayWinScreen();
     void clearBoard();
};

