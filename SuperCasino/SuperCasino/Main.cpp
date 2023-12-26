#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <Windows.h>
#include "games.h"
#include "leaderboard.h"
#include "utils.h"

using namespace std;

void displayMenu(const string& currentUsername, double currentBalance) {
    cout << "������, " << currentUsername << "!" << endl;
    cout << "1. ��� ������: $" << currentBalance << endl;
    cout << "2. ������� �������" << endl;
    cout << "3. ������" << endl;
    cout << "4. � �������" << endl;
    cout << "5. �����" << endl;
}

void displayModes() {
    cout << "1. ������ �����" << endl;
    cout << "2. ���� ����" << endl;
    cout << "3. �������" << endl;
    cout << "4. ��������" << endl;
    cout << "5. �����" << endl;
}

void AboutProject() {
    cout << endl;
    cout << endl;
    cout << "-----------------------------------------" << endl;
    cout << "������ Super Casino" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "� ������� ��������� �������:" << endl << endl;
    cout << "������� ���������" << endl;
    cout << "������� �����" << endl;
    cout << "������ �������" << endl;
    cout << "������� �������" << endl;
    cout << "������ ������" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "������� ��� ��������� ���!" << endl;
    cout << endl;
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "ru");
    string currentUsername;
    double currentBalance;

    vector<LeaderboardEntry> leaderboard;

    const string leaderboardFilename = "leaderboard.txt";

    loadLeaderboard(leaderboard, leaderboardFilename);

    cout << "������� ��� �������: ";
    cin >> currentUsername;

    currentBalance = getInitialBalance(leaderboard, currentUsername);

    while (true) {
        displayMenu(currentUsername, currentBalance);

        int choice;
        cout << "�������� �����: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "��� ������: $" << currentBalance << endl;
            break;
        case 2:
            displayLeaderboard(leaderboard);
            break;
        case 3:
            while (true) {
                displayModes();

                cout << "�������� �����: ";
                cin >> choice;

                switch (choice) {
                case 1:
                    playGuessNumber(currentBalance);
                    break;
                case 2:
                    BlackJack(currentBalance);
                    break;
                case 3:
                    CoinFlip(currentBalance);
                    break;
                case 4:
                    Hangman(currentBalance);
                case 5:
                    cout << "������� � ������� ����." << endl;
                    break;
                default:
                    cout << "�������� �����. ���������� �����." << endl;
                    break;
                }

                if (choice == 5) {
                    break;
                }

                updateLeaderboard(leaderboard, currentUsername, currentBalance);
            }
            break;
        case 4:
            AboutProject();
            break;
        case 5:
            saveLeaderboard(leaderboard, leaderboardFilename);
            cout << "��������� ���������." << endl;
            return 0;
        default:
            cout << "�������� �����. ���������� �����." << endl;
            break;
        }
    }

    return 0;
}
