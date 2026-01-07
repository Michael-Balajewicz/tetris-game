export module Block;

import <vector>;
import <memory>;
import Types;

export class Block {
protected:
    BlockType type;
    std::vector<Point> offsets; // 4 cells relative to origin (0,0)
    int levelCreated;

public:
    Block(BlockType t, std::vector<Point> off, int lvl);
    virtual ~Block() = default;

    BlockType getType() const;
    char getChar() const;
    int getLevelCreated() const;
    const std::vector<Point>& getOffsets() const;
    // int minimum(int x, int y);

    // rotation changes offsets only (board checks legality)
    virtual void rotateCW();
    virtual void rotateCCW();

    int getMaxRelRow() const;
};

export std::unique_ptr<Block> makeBlock(BlockType t, int levelCreated);
