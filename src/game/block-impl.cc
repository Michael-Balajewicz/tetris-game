module Block;

import <algorithm>;

Block::Block(BlockType t, std::vector<Point> off, int lvl)
    : type{t}, offsets{std::move(off)}, levelCreated{lvl} {}

BlockType Block::getType() const { return type; }
char Block::getChar() const { return blockTypeToChar(type); }
int Block::getLevelCreated() const { return levelCreated; }
const std::vector<Point>& Block::getOffsets() const { return offsets; }

// Mike
// int Block::minimum(int x, int y) {
//     if (x <= y) return x;
//     return y;
// }

void Block::rotateCW() {
    // Save the old lower-left anchor
    int oldMaxR = getMaxRelRow();
    int oldMinC = 0;
    for (auto &p : offsets) {
        oldMinC = std::min(oldMinC, p.c);
    }

    // Rotate around origin: (r, c) -> (c, -r)
    for (auto &p : offsets) {
        int nr = p.c;
        int nc = -p.r;
        p.r = nr;
        p.c = nc;
    }

    // Compute new lower-left corner
    int newMaxR = getMaxRelRow();
    int newMinC = 0;
    for (auto &p : offsets) {
        newMinC = std::min(newMinC, p.c);
    }

    // Compute translation so new LL → old LL
    int dr = oldMaxR - newMaxR;
    int dc = oldMinC - newMinC;

    // Apply translation
    for (auto &p : offsets) {
        p.r += dr;
        p.c += dc;
    }
}

void Block::rotateCCW() {
    // Save the old lower-left anchor
    int oldMaxR = getMaxRelRow();
    int oldMinC = 0;
    for (auto &p : offsets) {
        oldMinC = std::min(oldMinC, p.c);
    }

    // Rotate around origin: (r, c) -> (-c, r)
    for (auto &p : offsets) {
        int nr = -p.c;
        int nc = p.r;
        p.r = nr;
        p.c = nc;
    }

    // Compute new lower-left corner
    int newMaxR = getMaxRelRow();
    int newMinC = 0;
    for (auto &p : offsets) {
        newMinC = std::min(newMinC, p.c);
    }

    // Compute translation so new LL → old LL
    int dr = oldMaxR - newMaxR;
    int dc = oldMinC - newMinC;

    // Apply translation
    for (auto &p : offsets) {
        p.r += dr;
        p.c += dc;
    }
}

// Lorena new
int Block::getMaxRelRow() const {
    int maxR = offsets[0].r;
    for (auto &p : offsets) {
        maxR = std::max(maxR, p.r);
    }
    return maxR;
}

std::unique_ptr<Block> makeBlock(BlockType t, int lvl) {
    // initial blcoks based on :contentReference[oaicite:3]{index=3}
    
    // Mike new
    if (t == BlockType::I) {
        return std::make_unique<Block>(t, std::vector<Point>{{0,0},{0,1},{0,2},{0,3}}, lvl);
    } else if (t == BlockType::J) {
        return std::make_unique<Block>(t, std::vector<Point>{{0,0},{1,0},{1,1},{1,2}}, lvl);
    } else if (t == BlockType::L) {
        return std::make_unique<Block>(t, std::vector<Point>{{0,2},{1,0},{1,1},{1,2}}, lvl);
    } else if (t == BlockType::O) {
        return std::make_unique<Block>(t, std::vector<Point>{{0,0},{0,1},{1,0},{1,1}}, lvl);
    } else if (t == BlockType::S) {
        return std::make_unique<Block>(t, std::vector<Point>{{0,1},{0,2},{1,0},{1,1}}, lvl);
    } else if (t == BlockType::Z) {
        return std::make_unique<Block>(t, std::vector<Point>{{0,0},{0,1},{1,1},{1,2}}, lvl);
    } else if (t == BlockType::T) {
        return std::make_unique<Block>(t, std::vector<Point>{{0,0},{0,1},{0,2},{1,1}}, lvl);
    } else {
        return std::make_unique<Block>(t, std::vector<Point>{{0,0}}, lvl);
    }
}
