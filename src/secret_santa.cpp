#include "secret_santa.hpp"
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <stack>
#include <utility>
#include <random>

void undoExcludeList(std::vector<std::vector<int>> &candidates, const std::vector<std::vector<int>> &siblings, const int& receiver) {
    for (int i = 0; i < candidates.size(); ++i) {
        if (std::find(begin(siblings[i]), end(siblings[i]), receiver) == std::end(siblings[i]) && i != receiver)
            candidates[i][receiver] = 1;
    }
}

std::vector<int> chooseGiftReceiver(std::vector<std::vector<int>>& candidates, std::vector<std::vector<int>> siblings, int startingCandidateIndex, std::vector<int> result, std::stack<std::pair<int, int>> state, std::pair<int, std::vector<int>> checkpoint) {
    result.assign(candidates.size(), -1);
    
    if (startingCandidateIndex == -1) {
        std::random_device device;
        std::mt19937 rng(device());
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, candidates.size() - 1);

        startingCandidateIndex = dist(rng);
    }

    if (checkpoint.first == -1)
        checkpoint = {startingCandidateIndex, candidates[startingCandidateIndex]};
    // else5

    std::vector<int> potentialGiftReceiver = {};
    while (state.size() < candidates.size()) {
        potentialGiftReceiver.clear();

        for(int i = 0; i < checkpoint.second.size(); ++i) {
            if(checkpoint.second[i] == 1 && (i != startingCandidateIndex || state.size() == candidates.size() - 1)) {
                potentialGiftReceiver.push_back(i);
            }
        }

        if (potentialGiftReceiver.empty()) {
            std::pair<int, int> prevState = state.top();
            state.pop();

            undoExcludeList(candidates, siblings, prevState.second);

            candidates[prevState.first][prevState.second] = 0;

            bool shouldExcludeParentLeaf = true;
            for (int i = 0; i < candidates[prevState.first].size(); ++i) {
                if (candidates[prevState.first][i] == 1 && i != startingCandidateIndex) {
                    shouldExcludeParentLeaf = false;
                }
            }

            if (shouldExcludeParentLeaf && state.size() > 1) {

                std::pair<int, int> parentLeaf = state.top();
                candidates[parentLeaf.first][parentLeaf.second] = 0;
                candidates[prevState.first][prevState.second] = 1;
                
                state.pop();
                chooseGiftReceiver(candidates, siblings, startingCandidateIndex, result, state, {parentLeaf.first, candidates[parentLeaf.first]});
            } else if (shouldExcludeParentLeaf && state.size() == 1) {
                candidates[prevState.first][prevState.second] = 0;
            }   
            

            chooseGiftReceiver(candidates, siblings, startingCandidateIndex, result, state, {prevState.first, candidates[prevState.first]});
        }

        std::random_device device;
        std::mt19937 rng(device());
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, potentialGiftReceiver.size() - 1);

        std::pair<int, int> currentState = std::make_pair(checkpoint.first, potentialGiftReceiver[potentialGiftReceiver.size() > 1 ? rand() % potentialGiftReceiver.size() : 0]);
        state.push(currentState);

        if (state.size() == candidates.size())
            continue;

        for(int i = 0; i < candidates.size(); ++i) {
            candidates[i][currentState.second] = 0;
        }

        checkpoint = {currentState.second, candidates[currentState.second]};
    }

    for (int i = 0; i < candidates.size(); ++i) {
        std::pair<int, int> giftReceiver = state.top();
        result[giftReceiver.first] = giftReceiver.second;
        state.pop();
    }
    
    return result;
}