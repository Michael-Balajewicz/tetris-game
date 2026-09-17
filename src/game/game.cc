export module Game;

import <vector>;
import Player;
import TextDisplay;
import CommandInterpreter;
import Types;  // for BlockType

export class Game {
    Player p1;
    Player p2;
    TextDisplay td;
    CommandInterpreter parser;

    int turn = 0; // starts with p1
    bool gameOver = false;

public:
    // REMOVE NULLPTR???
    Game(int startLevel = 0, const std::vector<BlockType> *seq1 = nullptr, const std::vector<BlockType> *seq2 = nullptr);
    void run();
};
