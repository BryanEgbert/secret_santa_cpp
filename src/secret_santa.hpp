#pragma once
#include <iostream>
#include <vector>
#include <stack>

typedef struct Candidate {
    std::string name;
    std::vector<Candidate*> potentialGiftReceiver = {};
    std::string* giftReceiver = nullptr;
    std::vector<std::string> visited = {};
}Candidate;

std::vector<int> chooseGiftReceiver(std::vector<std::vector<int>>& candidates, std::vector<std::vector<int>> siblings, int startingCandidateIndex = -1, std::vector<int> result = {}, std::stack<std::pair<int, int>> state = {}, std::pair<int, std::vector<int>> checkpoint = {-1, {}});

Candidate getNextCandidate(const std::string& previousGiftReceiver, const std::vector<Candidate>& candidates, std::vector<std::string> excludes);

void undoExcludeList(std::vector<std::vector<int>> &candidates, const std::vector<std::vector<int>> &siblings, const int& receiver);