export module CommandInterpreter;

import <string>;
import Types;

export class CommandInterpreter {
public:
    struct theParse {
        int mult;
        CommandType cmd;
        char forced;
        theParse(int mult, CommandType cmd, char forced);
    };
    //some helpers
    bool startsWith(const std::string &s, const std::string &p) const;
    bool isADigit(char c) const;

    // returns (multiplier, commandType, optional forced block char)
    theParse parse(const std::string &line) const;
};
