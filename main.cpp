
#include <string>
#include <iostream>

#include "Mtmchkin.h"

using std::string;
using std::cout;
using std::endl;
using std::exception;

static const int REQUIRED_PARAMS_COUNT = 3;
static const int DECK_PATH_INDEX = 1;
static const int PLAYERS_PATH_INDEX = 2;

int main(int argc, char** argv) {
    if (argc != REQUIRED_PARAMS_COUNT) {
        cout << argc << endl;
        cout << "Invalid number of arguments" << endl;
        cout << "Usage: mtmchkin <deck_file_path> <players_file_path>" << endl;
    }
    string deckPath = "C:\\Users\\mhmda\\OneDrive\\Desktop\\New folder\\test13.deck";
    string playersPath = "C:\\Users\\mhmda\\OneDrive\\Desktop\\New folder\\test13.in";
    try {
        Mtmchkin game(deckPath, playersPath);
        game.play();
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }
}
