#include "src/secret_santa.hpp"
#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <random>
// #include "secret_santa.cpp"

int main(int, char**) {
    std::vector<std::vector<int>> fakePlayers = {
        {0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1},
        {1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1},
        {0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1},
        {0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
        {0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1},
        {1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1},
        {1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1},
        {0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1},
        {1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    };

    std::vector<std::vector<int>> playersSiblings = {
        {4, 7, 1, 8},
        {6, 8, 4, 2},
        {3, 5, 0, 1},
        {2, 5, 0, 4},
        {0, 7, 2, 6}, 
        {2, 3, 8, 7},
        {1, 8, 5},
        {0, 4, 6, 3},
        {1, 6, 3, 7},
        {10},
        {9},
    };

    auto lol = chooseGiftReceiver(fakePlayers, playersSiblings);


    std::random_device device;
    std::mt19937 rng(device());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, lol.size());

    for(int i = 0; i < lol.size(); ++i) {
        std::cout << i << " -> " << lol[i] << '\n';
    }
    // for (const auto& player : lol) {
    //     std::cout << player.name << " -> " << player.giftReceiver << '\n';
    // }
}