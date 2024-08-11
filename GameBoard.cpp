#include "GameBoard.h"
#include "StartScreen.h"
GameBoard::GameBoard() {
    if (!m_font.loadFromFile("ClearSans-Regular.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }
    m_board.resize(m_rows);
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            m_board[i].emplace_back(m_rectSize);
        }
    }
    initBoard();
}

void GameBoard::run() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "2048");
    StartScreen screen{};
    bool inStartScreen{ true };
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();



            if (inStartScreen) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (screen.buttonPressed(m_mousePosition, *this)) {
                        inStartScreen = false;
                    }
                }
            }
            else if (endGame) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Num1) {
                        inStartScreen = true;
                        endGame = false;
                        clearBoard();
                    }
                }
            }
            else {
                placePlayer(event, closestPosition());
            }
        }
        m_mousePosition = sf::Mouse::getPosition(window);
        std::cout << "Mouse Position : (" << m_mousePosition.x << ", " << m_mousePosition.y << ")\n";
        // std::cout << isMouseWithinBoard() << '\n';
        movePlayerToMouse(isMouseWithinBoard());
        window.clear(sf::Color::Black);
        if (inStartScreen) {
            screen.displayStartScreen(window);
        }
        else {
            m_mousePosition = sf::Mouse::getPosition(window);
            movePlayerToMouse(isMouseWithinBoard());
            drawBoard(window);
            if (endGame) {
                window.clear(sf::Color::Transparent);
                displayWinScreen();
                window.draw(m_text);
                window.draw(m_otherText);
            }
        }
        window.display();


    }
}

bool GameBoard::isMouseWithinBoard() {
    int position1{ m_board[0][0].getTileXPosition() };
    int position2{ m_board[m_rows - 1][m_cols - 1].getTileXPosition() };
    if (m_mousePosition.x > position1 && m_mousePosition.x < position2) return true;
    return false;
}

void GameBoard::setMatchType(const gameType type) {
    std::cout << "set match type: " << static_cast<int>(type) << '\n';
    static_cast<int>(type) == 0 ? m_gameType = true : m_gameType = false;
}

void GameBoard::printPositions() {
    for (const auto& e : m_board) {
        for (const auto j : e) {
            std::cout << j.getTileXPosition() << '\n';
        }
    }
}

void GameBoard::movePlayerToMouse(bool mouseWithinBoard) {
    if (!mouseWithinBoard) {
        return;
    }
    else if (mouseWithinBoard) {
        auto closestColumn = std::min_element(columnPositions.begin(), columnPositions.end(),
            [this](int a, int b) {
                return std::abs(a - m_mousePosition.x) < std::abs(b - m_mousePosition.x);
            });
        if (closestColumn != columnPositions.end()) {
            player.setPosition(*closestColumn);
        }
    }
}

void GameBoard::placePlayer(sf::Event& event, int closestPosition) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (m_gameType) {
            // Find the column index corresponding to the closest position
            auto itr = m_map.find(closestPosition);
            if (itr == m_map.end()) {
                return; 
            }
            int col = itr->second;

            // Find the first empty row in the column
            int row = findFirstEmptyRow(col);
            if (row == -1) {
                return; 
            }

            // Place the player piece
            sf::Color color = player.getColor();
            m_board[row][col].setColor(color);
            //std::cout << "win: " << checkWin(col, row, color) << '\n';
            if (checkWin(col, row, color)) {
                endGame = true;
                return;
            }
            //player.changePlayerColor();
           // std::this_thread::sleep_for(std::chrono::milliseconds(350));
            aiMove();
        }
        else {
            // Find the column index corresponding to the closest position
            auto itr = m_map.find(closestPosition);
            if (itr == m_map.end()) {
                return; 
            }
            int col = itr->second;

           
            int row = findFirstEmptyRow(col);
            if (row == -1) {
                return; 
            }

            
            sf::Color color = player.getColor();
            m_board[row][col].setColor(color);
            //std::cout << "win: " << checkWin(col, row, color) << '\n';
            if (checkWin(col, row, color)) {
                endGame = true;
                return;
            }
            //player.changePlayerColor();
          //  std::this_thread::sleep_for(std::chrono::milliseconds(350));
            player.changePlayerColor();
        }
    }
}

void GameBoard::aiMove() {
    std::vector<int> validColumns;
    for (int col = 0; col < m_cols; ++col) {
        if (isColumnValid(col)) {
            validColumns.push_back(col);
        }
    }

    if (!validColumns.empty()) {
        int randomIndex = std::rand() % validColumns.size();
        int chosenColumn = validColumns[randomIndex];
        placePiece(chosenColumn, aiColor);
    }
}
bool GameBoard::checkWin(int col, int row, sf::Color& color) {
    //check  vertical pieces starting from bottom
    //create count variable and increment until we get 4  consecutive squares, if not set it to 0
    std::cout << col << " " << row << '\n';
    int count{ 0 };
    for (int r = m_rows - 1; r >= 0; --r) {
        if (m_board[r][col].getColor() == color) {
            count++;
        }
        else {
            count = 0;
        }
        if (count == 4) {
            return true;
        }
    }
    //check horizontal
    for (int c{ 0 }; c < m_cols; ++c) {
        if (m_board[row][c].getColor() == color) {
            count++;
        }
        else {
            count = 0;
        }
        if (count == 4) {
            return true;
        }
    }



    return checkDiagonal(col, row, color);
}

bool GameBoard::checkDiagonal(int col, int row, sf::Color& color) {
    // Check for diagonal wins (both directions)
    return checkDiagonalDirection(col, row, color, 1, 1) || checkDiagonalDirection(col, row, color, 1, -1);
}

bool GameBoard::checkDiagonalDirection(int col, int row, sf::Color& color, int colStep, int rowStep) {
    int count = 0;
    for (int i = -3; i <= 3; ++i) {
        int c = col + i * colStep;
        int r = row + i * rowStep;
        if (c >= 0 && c < m_cols && r >= 0 && r < m_rows && m_board[r][c].getColor() == color) {
            ++count;
        }
        else {
            count = 0;
        }
        if (count == 4) {
            return true;
        }
    }
    return false;
}

int GameBoard::findFirstEmptyRow(int col) {
    for (int row = m_rows - 1; row >= 0; --row) {
        if (m_board[row][col].isEmpty()) {
            return row;
        }
    }
    return -1; 
}

void GameBoard::displayWinScreen() {
    m_text.setFont(m_font);
    m_otherText.setFont(m_font);
    m_text.setString(player.getColorAsString() + " Wins!");
    m_otherText.setString("Press 1 to play again.");
    m_text.setCharacterSize(100);
    m_otherText.setCharacterSize(40);
    m_text.setFillColor(sf::Color::White);
    m_otherText.setFillColor(sf::Color::White);
    m_text.setPosition(200, 200);
    m_otherText.setPosition(200, 400);
}

void GameBoard::initBoard() {
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            m_board[i][j].setPosition(m_leftSpacing + j * (m_rectSize), m_topBottomSpacing + i * (m_rectSize));
        }
    }
}
void GameBoard::drawBoard(sf::RenderWindow& window) {
    player.draw(window);
    for (const auto& i : m_board) {
        for (const auto j : i) {
            j.draw(window);
        }
    }
}
int GameBoard::closestPosition() {
    auto closestColumn = std::min_element(columnPositions.begin(), columnPositions.end(),
        [this](int a, int b) {
            return std::abs(a - m_mousePosition.x) < std::abs(b - m_mousePosition.x);
        });
    return *closestColumn;
}
bool GameBoard::isColumnValid(int col) {
    return m_board[0][col].isEmpty();
}

void GameBoard::placePiece(int col, sf::Color color) {
    for (int row = m_rows - 1; row >= 0; --row) {
        if (m_board[row][col].isEmpty()) {
            m_board[row][col].setColor(color);
            break;
        }
    }
}
void GameBoard::clearBoard() {
    sf::Color color{ sf::Color::White };
    for (int i{ 0 }; i < m_rows; ++i) {
        for (int j{ 0 }; j < m_cols; ++j) {
            m_board[i][j].setColor(color);
        }
    }
}