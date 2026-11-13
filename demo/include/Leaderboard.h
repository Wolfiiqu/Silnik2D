#pragma once
#include <vector>
#include <string>

namespace game {
    class Leaderboard {
    private:
        std::vector<int> scores;
        const std::string filename = "../demo/highscores.txt";
        const size_t maxScores = 5;

    public:
        Leaderboard();
        void load();           // Wczytuje z pliku
        void save();           // Zapisuje do pliku
        void addScore(int score); // Dodaje nowy wynik i sortuje
        const std::vector<int>& getScores() const { return scores; }
    };
}