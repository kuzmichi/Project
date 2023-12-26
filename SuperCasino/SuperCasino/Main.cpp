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
    cout << "Привет, " << currentUsername << "!" << endl;
    cout << "1. Ваш баланс: $" << currentBalance << endl;
    cout << "2. Таблица лидеров" << endl;
    cout << "3. Режимы" << endl;
    cout << "4. О проекте" << endl;
    cout << "5. Выход" << endl;
}

void displayModes() {
    cout << "1. Угадай число" << endl;
    cout << "2. Блэк Джек" << endl;
    cout << "3. Монетка" << endl;
    cout << "4. Виселица" << endl;
    cout << "5. Назад" << endl;
}

void AboutProject() {
    cout << endl;
    cout << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Проект Super Casino" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "В проекте принимали участие:" << endl << endl;
    cout << "Кузьмич Александр" << endl;
    cout << "Хомутов Денис" << endl;
    cout << "Гуркин Тимофей" << endl;
    cout << "Лученок Алексей" << endl;
    cout << "Тишкин Богдан" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Спасибо что выбираете нас!" << endl;
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

    cout << "Введите ваш никнейм: ";
    cin >> currentUsername;

    currentBalance = getInitialBalance(leaderboard, currentUsername);

    while (true) {
        displayMenu(currentUsername, currentBalance);

        int choice;
        cout << "Выберите опцию: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Ваш баланс: $" << currentBalance << endl;
            break;
        case 2:
            displayLeaderboard(leaderboard);
            break;
        case 3:
            while (true) {
                displayModes();

                cout << "Выберите режим: ";
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
                    cout << "Возврат в главное меню." << endl;
                    break;
                default:
                    cout << "Неверный выбор. Попробуйте снова." << endl;
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
            cout << "Программа завершена." << endl;
            return 0;
        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
            break;
        }
    }

    return 0;
}
