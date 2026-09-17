module Game;

import <iostream>;
import <string>;
import Types;

using namespace std;

Game::Game(int startLevel, const std::vector<BlockType> *seq1, const std::vector<BlockType> *seq2): 
p1{startLevel, seq1}, p2{startLevel, seq2}, td{&p1, &p2} 
{
    p1.getBoard().attach(&td);
    p2.getBoard().attach(&td);
    p1.getBoard().notify();
    p2.getBoard().notify();
}

void Game::run() {
    string line;

    cout << "Welcome to Biquadris!" << endl;
    td.render();

    while (!gameOver && getline(cin, line)) {
        auto temp = parser.parse(line);
        auto mult = temp.mult;
        auto cmd = temp.cmd;
        auto forced = temp.forced;

        Player *active = (turn == 0 ? &p1 : &p2);

        if (cmd == CommandType::EOFCommand) break;

        if (forced != 0) {
            active->forceBlock(charToBlockType(forced));
        } else {
            for (int k = 0; k < mult; ++k) {
                if (cmd == CommandType::Left) {
                    active->moveLeft();
                }
                else if (cmd == CommandType::Right) {
                    active->moveRight();
                }
                else if (cmd == CommandType::Down) {
                    active->moveDown();
                }
                else if (cmd == CommandType::CW) {
                    active->rotateCW();
                }
                else if (cmd == CommandType::CCW) {
                    active->rotateCCW();
                }
                else if (cmd == CommandType::LevelUp) {
                    active->levelUp();
                }
                else if (cmd == CommandType::LevelDown) {
                    active->levelDown();
                }
                else if (cmd == CommandType::Restart) {
                    p1.reset();
                    p2.reset();
                    turn = 0;
                }
                else if (cmd == CommandType::Drop) {
                    active->drop();
                    // dont call spawnNext() for the player whose turn starting
                    // only the player who dropped should get a new block (alrady in player:;drop())
                    // check if next players current block can be placed at their spawn
                    // position; if not, the game is over.
                    if (!active->getBoard().canPlace(active->getCurrentBlock(), active->getCurR(), active->getCurC())) {
                        active->setCurR(-1); // cant place (by MY definition)
                        gameOver = true;
                    }

                    // switch player turn after drop
                    turn = 1 - turn;
                    active = (turn == 0 ? &p1 : &p2);
                }
                else {
                    // nothing i guess
                }

            }
        }

        p1.getBoard().notify();
        p2.getBoard().notify();
        td.render();

        if (gameOver) {
            cout << "Game Over! Player " << (1-turn) << " wins" << endl;
        }
    }
}
