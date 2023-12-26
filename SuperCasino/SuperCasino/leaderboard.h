#pragma once
#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <vector>
#include <string>

struct LeaderboardEntry {
    std::string username;
    double balance;
};

void saveLeaderboard(const std::vector<LeaderboardEntry>& leaderboard, const std::string& filename);
void loadLeaderboard(std::vector<LeaderboardEntry>& leaderboard, const std::string& filename);
void displayLeaderboard(const std::vector<LeaderboardEntry>& leaderboard);
double getInitialBalance(const std::vector<LeaderboardEntry>& leaderboard, const std::string& username);
void updateLeaderboard(std::vector<LeaderboardEntry>& leaderboard, const std::string& username, double balance);

#endif