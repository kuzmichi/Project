#include "leaderboard.h"
#include <iostream>
#include <fstream>
#include <algorithm>

void saveLeaderboard(const std::vector<LeaderboardEntry>& leaderboard, const std::string& filename) {
    std::ofstream file(filename);

    if (file.is_open()) {
        for (const LeaderboardEntry& entry : leaderboard) {
            file << entry.username << " " << entry.balance << std::endl;
        }
        file.close();
    }
    else {
        std::cout << "Ошибка сохранения таблицы лидеров." << std::endl;
    }
}

void loadLeaderboard(std::vector<LeaderboardEntry>& leaderboard, const std::string& filename) {
    std::ifstream file(filename);

    if (file.is_open()) {
        leaderboard.clear();

        std::string username;
        double balance;

        while (file >> username >> balance) {
            LeaderboardEntry entry;
            entry.username = username;
            entry.balance = balance;
            leaderboard.push_back(entry);
        }

        file.close();
    }
    else {
        std::cout << "Ошибка загрузки таблицы лидеров." << std::endl;
    }
}

void displayLeaderboard(const std::vector<LeaderboardEntry>& leaderboard) {
    std::cout << "Таблица лидеров:" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "Никнейм\t\t\tБаланс" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;

    for (const LeaderboardEntry& entry : leaderboard) {
        std::cout << entry.username << "\t\t\t$" << entry.balance << std::endl;
    }

    std::cout << "-----------------------------------------" << std::endl;
}

double getInitialBalance(const std::vector<LeaderboardEntry>& leaderboard, const std::string& username) {
    auto it = std::find_if(leaderboard.begin(), leaderboard.end(), [&username](const LeaderboardEntry& entry) {
        return entry.username == username;
        });

    if (it != leaderboard.end()) {
        return it->balance;
    }
    else {
        return 500.0;
    }
}

void updateLeaderboard(std::vector<LeaderboardEntry>& leaderboard, const std::string& username, double balance) {
    auto it = std::find_if(leaderboard.begin(), leaderboard.end(), [&username](const LeaderboardEntry& entry) {
        return entry.username == username;
        });

    if (it != leaderboard.end()) {
        it->balance = balance;
    }
    else {
        LeaderboardEntry entry;
        entry.username = username;
        entry.balance = balance;
        leaderboard.push_back(entry);
    }

    std::sort(leaderboard.begin(), leaderboard.end(), [](const LeaderboardEntry& a, const LeaderboardEntry& b) {
        return a.balance > b.balance;
        });
}