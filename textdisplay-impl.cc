module TextDisplay;

import <iostream>;
import <string>;
import Abstract;
import Board;
import Player;

using namespace std;

// space for next block display
const int rowsForNext = 2;
const int colsForNext = 4;

TextDisplay::TextDisplay(Player *a, Player *b) : p1{a}, p2{b} {}

void TextDisplay::update(Subject &) {
    buffer.clear();

    buffer.push_back("Level: " + std::to_string(p1->getLevelNum()) + "        Level: " + std::to_string(p2->getLevelNum()));
    buffer.push_back("Score: " + std::to_string(p1->getScore().getCurrent()) + "        Score: " + std::to_string(p2->getScore().getCurrent()));
    buffer.push_back("     High Score: " + std::to_string(p1->getScore().getHi()));
    buffer.push_back("----------- -----------");

    auto g1 = p1->getBoard().renderWithCurrent(p1->getCurrentBlock(), p1->getCurR(), p1->getCurC());
    auto g2 = p2->getBoard().renderWithCurrent(p2->getCurrentBlock(), p2->getCurR(), p2->getCurC());

    for (int r = 0; r < Board::Rows; ++r) {
        string line1; 
        string line2;
        for (int c = 0; c < Board::Cols; ++c) line1 += (g1[r][c] == ' ' ? '.' : g1[r][c]);
        for (int c = 0; c < Board::Cols; ++c) line2 += (g2[r][c] == ' ' ? '.' : g2[r][c]);

        buffer.push_back(line1 + " " + line2);
    }

    buffer.push_back("----------- -----------");
    buffer.push_back("Next:       Next:");

    // ***
    // display the actual block not just the type
    
    // should be of type vector<Point> (where origin is 0,0 so need to offset p2's grid by a bit)
    auto p1nextBlockPoints = p1->getNextBlock().getOffsets();
    auto p2nextBlockPoints = p2->getNextBlock().getOffsets();
    char p1Char = p1->getNextBlock().getChar();
    char p2Char = p2->getNextBlock().getChar();

    // need to put it in a grid (2 rows x 4 cols)
    vector<std::vector<char>> p1Next(rowsForNext, std::vector<char>(colsForNext, ' '));
    vector<std::vector<char>> p2Next(rowsForNext, std::vector<char>(colsForNext, ' '));

    for (auto &p : p1nextBlockPoints) {
        p1Next[p.r][p.c] = p1Char;
    }

    for (auto &p : p2nextBlockPoints) {
        p2Next[p.r][p.c] = p2Char;
    }

    // display grid
    for (int r = 0; r < rowsForNext; ++r) {
        string line1;
        string line2;
        for (int c = 0; c < colsForNext; ++c) {
            line1 += (p1Next[r][c] == ' ' ? ' ' : p1Next[r][c]);
        }
        for (int c = 0; c < colsForNext; ++c) {
            line2 += (p2Next[r][c] == ' ' ? ' ' : p2Next[r][c]);
        }
        buffer.push_back(line1 + "        " + line2);
    }
}

void TextDisplay::render() const {
    for (auto &line : buffer) cout << line << endl;
}
