module CommandInterpreter;

using namespace std;

CommandInterpreter::theParse::theParse(int mult, CommandType cmd, char forced): mult{mult}, cmd{cmd}, forced{forced} {}


//not workings (REMOVE LATER??)
bool CommandInterpreter::startsWith(const std::string &s, const std::string &p) const {
    return s.size() >= p.size() && s.substr(0, p.size()) == p;
}

bool CommandInterpreter::isADigit(char c) const {
    return c >= '0' && c <= '9';
}


// Mike new
CommandInterpreter::theParse CommandInterpreter::parse(const std::string &line) const {
    if (line.empty()) return theParse{1, CommandType::Invalid, 0};

    int i = 0;
    int mult = 0;

    // added static_cast to remove warnings of type comparison, signed vs unsigned
    while (i < static_cast<int>(line.size()) && isADigit(line[i])) {
        mult = mult * 10 + (line[i] - '0');
        i++;
    }

    if (mult == 0) mult = 1;
    string cmd = line.substr(i);

    if (cmd == "EOF") return theParse{1, CommandType::EOFCommand, 0};
    if (cmd == "exit") return theParse{1, CommandType::EOFCommand, 0};

    if (startsWith(cmd, "left")) return theParse{mult, CommandType::Left, 0};
    if (startsWith(cmd, "right")) return theParse{mult, CommandType::Right, 0};
    if (startsWith(cmd, "down")) return theParse{mult, CommandType::Down, 0};
    if (startsWith(cmd, "drop")) return theParse{mult, CommandType::Drop, 0};
    if (startsWith(cmd, "clockwise")) return theParse{mult, CommandType::CW, 0};
    if (startsWith(cmd, "counterclockwise")) return theParse{mult, CommandType::CCW, 0};
    if (startsWith(cmd, "levelup")) return theParse{mult, CommandType::LevelUp, 0};
    if (startsWith(cmd, "leveldown")) return theParse{mult, CommandType::LevelDown, 0};
    if (startsWith(cmd, "restart")) return theParse{1, CommandType::Restart, 0};

    // testing the single blocks
    if (cmd.size() == 1) {
        if (cmd[0] == 'I' || cmd[0] == 'J' || cmd[0] == 'L' || cmd[0] == 'O' || cmd[0] == 'S' || cmd[0] == 'T' || cmd[0] == 'Z') {
            return theParse{1, CommandType::Invalid, cmd[0]};
        }
    }
    // if (cmd.size() == 1 && string("IJLOSTZ").find(cmd[0]) != std::string::npos) {
    //     return theParse{1, CommandType::Invalid, cmd[0]};
    // }

    return theParse{1, CommandType::Invalid, 0};

}
