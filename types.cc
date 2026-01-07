export module Types;

import <utility>;
import <vector>;
import <string>;

export struct Point {
    int r;
    int c;
};

export enum class BlockType { I, J, L, O, S, Z, T, Star};

export enum class CommandType {
    Left, Right, Down, Up, Drop,
    CW, CCW,
    LevelUp, LevelDown,
    Restart,
    Invalid, EOFCommand
};

export BlockType charToBlockType(char ch);
export char blockTypeToChar(BlockType t);
