export module Board;

import <vector>;
import <memory>;
import Abstract;
import Types;
import Block;

export class Board : public Subject {
public:
    //bruh remove ts
    // const int should be fine lowk
    // and if anything move this down to other public section
    // two public sections look weird
    static constexpr int Rows = 18;
    static constexpr int Cols = 11;

private:
    std::vector<std::vector<char>> grid; // starts with ' ' (as empty then '.' looks nicer)

    int originR = 3; // spawn row (after reserve)
    int originC = 0; // spawn col

public:
    Board();

    void reset();

    const std::vector<std::vector<char>>& getGrid() const;

    bool canPlace(const Block &b, int baseR, int baseC) const;
    void place(const Block &b, int baseR, int baseC);

    bool canMove(const Block &b, int baseR, int baseC, int dr, int dc) const;

    int clearFullRows();

    // draw current block on a temp copy (for display)
    std::vector<std::vector<char>> renderWithCurrent(const Block &b, int baseR, int baseC) const;
};
