module Types;

BlockType charToBlockType(char ch) {
    if (ch == 'I') {
        return BlockType::I;
    }
    else if (ch == 'J') {
        return BlockType::J;
    }
    else if (ch == 'L') {
        return BlockType::L;
    }
    else if (ch == 'O') {
        return BlockType::O;
    }
    else if (ch == 'S') {
        return BlockType::S;
    }
    else if (ch == 'Z') {
        return BlockType::Z;
    }
    else if (ch == 'T') {
        return BlockType::T;
    }
    else if (ch == '*') {
        return BlockType::Star;
    }
    else {
        return BlockType::I; // default to I block (by MY definition)
    }
}

char blockTypeToChar(BlockType t) {
    if (t == BlockType::I) {
        return 'I';
    }
    else if (t == BlockType::J) {
        return 'J';
    }
    else if (t == BlockType::L) {
        return 'L';
    }
    else if (t == BlockType::O) {
        return 'O';
    }
    else if (t == BlockType::S) {
        return 'S';
    }
    else if (t == BlockType::Z) {
        return 'Z';
    }
    else if (t == BlockType::T) {
        return 'T';
    }
    else if (t == BlockType::Star) {
        return '*';
    }
    else {
        return '?'; 
        // should never happen
        // added to remove warnings
    }
}
