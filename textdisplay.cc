export module TextDisplay;

import <string>;
import <vector>;
import Abstract;
import Player;
import Types;

export class TextDisplay : public Observer {
    Player *p1;
    Player *p2;
    std::vector<std::string> buffer;

public:
    TextDisplay(Player *a, Player *b);

    void update(Subject &whoNotified) override;
    void render() const;
};
