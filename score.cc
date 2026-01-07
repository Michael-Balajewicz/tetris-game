export module Score;

export class Score {
    int current = 0;
    int hi = 0;
public:
    void resetCurrent();
    void addLinesCleared(int level, int lines);
    void addBlockCleared(int levelCreated);

    int getCurrent() const;
    int getHi() const;
};
