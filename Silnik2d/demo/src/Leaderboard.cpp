#include "../include/Leaderboard.h"
#include <fstream>
#include <algorithm>
#include <iostream>

namespace game {

    Leaderboard::Leaderboard() {
        load();
    }

    void Leaderboard::load() {
        scores.clear();
        std::ifstream file(filename);
        if (!file.is_open()) return;

        int s;
        while (file >> s) {
            scores.push_back(s);
        }
        file.close();
        

        std::sort(scores.begin(), scores.end(), std::greater<int>());
        if (scores.size() > maxScores) {
            scores.resize(maxScores);
        }
    }

    void Leaderboard::save() {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Nie mozna zapisac pliku " << filename << "\n";
            return;
        }
        for (int s : scores) {
            file << s << "\n";
        }
        file.close();
    }

    void Leaderboard::addScore(int score) {
        scores.push_back(score);
        std::sort(scores.begin(), scores.end(), std::greater<int>());
        if (scores.size() > maxScores) {
            scores.resize(maxScores);
        }
        save();
    }

}