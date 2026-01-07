import <iostream>;
import <fstream>;
import <string>;
import <vector>;
import <cstdlib>;
import Game;
import Types;

using namespace std;

struct Config {
    int seed = 1;
    int startLevel = 0;
    string scriptfile1 = "biquadris_sequence1.txt"; 
    string scriptfile2 = "biquadris_sequence2.txt";
};


Config parseArgs(int argc, char *argv[]) {
    Config cfg;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];

        if (arg == "-seed" && i + 1 < argc) {
            cfg.seed = stoi((argv[++i]));
        } else if (arg == "-startlevel" && i + 1 < argc) {
            cfg.startLevel = stoi(argv[++i]);
        } else if (arg == "-scriptfile1" && i + 1 < argc) {
            cfg.scriptfile1 = argv[++i];
        } else if (arg == "-scriptfile2" && i + 1 < argc) {
            cfg.scriptfile2 = argv[++i];
        } else {
            cerr << "************* BAD arguments! *************" << endl;
            exit(1);
        }
    }

    return cfg;
}

vector<BlockType> loadSequence(const string &filename) {
    ifstream in{filename};
    if (!in) {
        cerr << "Error: could not open sequence file " << filename << endl;
        exit(1);
    }

    vector<BlockType> seq;
    char c;
    while (in >> c) {
        if (c == 'I') {
            seq.push_back(BlockType::I);
        }
        else if (c == 'J') {
            seq.push_back(BlockType::J);
        }
        else if (c == 'L') {
            seq.push_back(BlockType::L);
        }
        else if (c == 'O') {
            seq.push_back(BlockType::O);
        }
        else if (c == 'S') {
            seq.push_back(BlockType::S);
        }
        else if (c == 'T') {
            seq.push_back(BlockType::T);
        } 
        else if (c == 'Z') {
            seq.push_back(BlockType::Z);
        }
        else { // one by one for default
            seq.push_back(BlockType::Star);
        }
    }

    if (seq.empty()) {
        cerr << "Error: sequence file " << filename << " is empty!" << endl;
        exit(1);
    }

    return seq;
}




int main(int argc, char *argv[]) {
    Config cfg = parseArgs(argc, argv);
    vector<BlockType> seq1 = loadSequence(cfg.scriptfile1);
    vector<BlockType> seq2 = loadSequence(cfg.scriptfile2);

    // set rand rng
    srand(cfg.seed);

    Game g{cfg.startLevel, (cfg.startLevel == 0 ? &seq1 : nullptr), (cfg.startLevel == 0 ? &seq2 : nullptr)};

    g.run();
}
