module Level;

import <vector>;
import <cstdlib>;
import <memory>;
import Types;
import Block;

using namespace std;

Level::Level(int n) : levelNum{n} {}
int Level::getLevelNum() const {
    return levelNum;
}
// bool Level::isHeavy() override const {
//     return false;
// }


class Level0 : public Level {
    vector<BlockType> seq;
    int index;
public:
    Level0(const std::vector<BlockType> &sequence) : Level{0}, seq{sequence}, index{0} {}

    unique_ptr<Block> createBlock() override {
        BlockType type = seq[index];
        index++;
        if (index == seq.size()) {
            index = 0;
        }
        return makeBlock(type, levelNum);

    }

};


class Level1 : public Level {
public:
    Level1() : Level{1} {}

    unique_ptr<Block> createBlock() override {
        int r = std::rand() % 12;
        //[0, 11]

        BlockType type;

        // z and s have 1/12
        // everything else should have 1/6 so 2/12
        if (r == 0) type = BlockType::Z;
        else if (r == 1) type = BlockType::S;
        else if (r < 4) type = BlockType::I;
        else if (r < 6) type = BlockType::J;
        else if (r < 8) type = BlockType::T;
        else if (r < 10) type = BlockType::L;
        else type = BlockType::O;

        return makeBlock(type, levelNum);
    }

};


class Level2 : public Level {
public:
    Level2() : Level{2} {}

    unique_ptr<Block> createBlock() override {
        int r = std::rand() % 7;
        // [0, 6]
        
        BlockType type;

        // everything should have 1/6
        if (r == 0) type = BlockType::Z;
        else if (r == 1) type = BlockType::S;
        else if (r == 2) type = BlockType::I;
        else if (r == 3) type = BlockType::J;
        else if (r == 4) type = BlockType::T;
        else if (r == 5) type = BlockType::L;
        else type = BlockType::O;

        return makeBlock(type, levelNum);
    }
};


// add Heavy effect when specail actions gets implemented
class Level3 : public Level {
public:
    Level3(): Level{3} {}

    unique_ptr<Block> createBlock() override {
        int r = std::rand() % 9; 
        // [0, 8]
        BlockType type;

        // s and z have 2/9 and everything else is equal
        // so s and z are twice as likely to spawn than I, J, L, O or t
        if (r < 2) type = BlockType::S;
        else if (r < 4) type = BlockType::Z;
        else if (r == 4) type = BlockType::I;
        else if (r == 5) type = BlockType::J;
        else if (r == 6) type = BlockType::L;
        else if (r == 7) type = BlockType::O;
        else type = BlockType::T;

        return makeBlock(type, levelNum);
    }
    

};


unique_ptr<Level> makeLevel0(const std::vector<BlockType> &sequence) {
    // upcasting??
    return std::make_unique<Level0>(sequence);
}

unique_ptr<Level> makeLevel(int n) {
    if (n == 1) return std::make_unique<Level1>();
    else if (n == 2) return std::make_unique<Level2>();
    else return std::make_unique<Level3>();
    // add level4 later
}
