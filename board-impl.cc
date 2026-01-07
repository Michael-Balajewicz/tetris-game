module Board;

Board::Board() : grid(Rows, std::vector<char>(Cols, ' ')) {}

void Board::reset() {
    for (auto &row : grid) {
        for (auto &cell : row) {
            cell = ' ';
        }
    }
    // render
    notify();
}

const std::vector<std::vector<char>>& Board::getGrid() const { return grid; }

bool Board::canPlace(const Block &b, int baseR, int baseC) const {
    for (auto &off : b.getOffsets()) {
        int r = baseR + off.r;
        int c = baseC + off.c;

        if (r < 0 || r >= Rows || c < 0 || c >= Cols) return false; // Lorena edited, changed r < 3 to r < 0
        if (grid[r][c] != ' ') return false;
    }
    return true;
}

void Board::place(const Block &b, int baseR, int baseC) {
    for (auto &off : b.getOffsets()) {
        int r = baseR + off.r;
        int c = baseC + off.c;
        grid[r][c] = b.getChar();
    }
    // re-render the board
    notify();
}
 
bool Board::canMove(const Block &b, int baseR, int baseC, int dr, int dc) const {
    return canPlace(b, baseR + dr, baseC + dc);
}

int Board::clearFullRows() {
    int cleared = 0;
    for (int r = 0; r < Rows; ++r) {
        bool full = true;
        for (int c = 0; c < Cols; ++c) {
            if (grid[r][c] == ' ') { full = false; break; }
        }
        if (full) {
            cleared++;
            // drop everything above down by 1
            for (int rr = r; rr > 0; --rr) {
                grid[rr] = grid[rr-1];
            }
            grid[0] = std::vector<char>(Cols, ' ');
        }
    }
    if (cleared > 0) notify();
    return cleared;
}

std::vector<std::vector<char>> Board::renderWithCurrent(const Block &b, int baseR, int baseC) const {
    auto tmp = grid;
    if (baseR == -1) return tmp; // if game over, just return the grid
    for (auto &off : b.getOffsets()) {
        int r = baseR + off.r;
        int c = baseC + off.c;
        if (r >= 0 && r < Rows && c >= 0 && c < Cols)
            tmp[r][c] = b.getChar();
    }
    return tmp;
}
