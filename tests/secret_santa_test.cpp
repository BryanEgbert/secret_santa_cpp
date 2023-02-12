#include <algorithm>
#include <gtest/gtest.h>
#include <iterator>
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "../src/secret_santa.hpp"

TEST(SecretSantaUtilsTest, undoExcludeList) {
    std::vector<std::vector<int>> fakePlayers = {
        {0, 0, 0, 1, 0, 1, 1, 0, 0},
        {1, 0, 0, 1, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 1, 1, 1},
        {0, 1, 0, 0, 0, 0, 1, 1, 1},
        {0, 1, 0, 1, 0, 1, 0, 0, 1},
        {1, 1, 0, 0, 1, 0, 1, 0, 0},
        {1, 0, 0, 1, 1, 0, 0, 1, 1},
        {0, 1, 0, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 1, 1, 1, 0, 0},
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
    };

    undoExcludeList(fakePlayers, playersSiblings, 2);

    for (int i = 0; i < fakePlayers.size(); ++i) {
        if (std::find(begin(playersSiblings[i]), end(playersSiblings[i]), 2) != std::end(playersSiblings[i]) || i == 2) {
            EXPECT_EQ(fakePlayers[i][2], 0);
        } else {
            EXPECT_EQ(fakePlayers[i][2], 1);
        }
    }
}

TEST(SecretSantaTest, chooseGiftReceiver) {
    std::vector<std::vector<int>> fakePlayers = {
        {0, 0, 1, 1, 0, 1, 1, 0, 0},
        {1, 0, 0, 1, 1, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 1, 1, 1},
        {0, 1, 0, 0, 0, 0, 1, 1, 1},
        {0, 1, 0, 1, 0, 1, 0, 0, 1},
        {1, 1, 0, 0, 1, 0, 1, 0, 0},
        {1, 0, 1, 1, 1, 0, 0, 1, 1},
        {0, 1, 1, 0, 0, 1, 0, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 0, 0},
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
    };

    auto result = chooseGiftReceiver(fakePlayers, playersSiblings);
    std::vector<int> exclude = {};

    for (int i = 0; i < fakePlayers.size(); ++i) {
        EXPECT_EQ(fakePlayers[i][result[i + 1]], 0);
        EXPECT_EQ(std::find(begin(exclude), end(exclude), result[i]), std::end(exclude)) << "User " << result[i] << " already got a gift from someone else";
        exclude.push_back(result[i]);

        for (int j = 0; j < fakePlayers.size(); ++j) {
            fakePlayers[j][result[i + 1]] = 0;
        }
    }

    EXPECT_FALSE(result.empty()) << "vector is empty " << result.size();
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}