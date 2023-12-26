#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <Windows.h>

using namespace std;

struct LeaderboardEntry {
    string username;
    double balance;
};

void saveLeaderboard(const vector<LeaderboardEntry>& leaderboard, const string& filename) {
    ofstream file(filename);

    if (file.is_open()) {
        for (const LeaderboardEntry& entry : leaderboard) {
            file << entry.username << " " << entry.balance << endl;
        }
        file.close();
    }
    else {
        cout << "������ ���������� ������� �������." << endl;
    }
}

void loadLeaderboard(vector<LeaderboardEntry>& leaderboard, const string& filename) {
    ifstream file(filename);

    if (file.is_open()) {
        leaderboard.clear();

        string username;
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
        cout << "������ �������� ������� �������." << endl;
    }
}

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

int generateRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void playGuessNumber(double& balance) {
    const int minNumber = 1;
    const int maxNumber = 100;

    int secretNumber = generateRandomNumber(minNumber, maxNumber);

    cout << "����� ���������� � ���� '������ �����'!" << endl;
    cout << "� ������� ����� �� " << minNumber << " �� " << maxNumber << ". ���������� �������!" << endl;

    int attempts = 0;
    int guess;
    double bet;
    do {
        cout << "������� ���� ������ (0 ��� ������ �� ����): ";
        cin >> bet;

        if (bet == 0) {
            return;
        }

        if (bet < 0 || bet > balance) {
            cout << "������������ ������. ����������, ������� ������ �� 0 �� ������ �������� �������." << endl;
        }
             } while (bet < 0 || bet > balance);
 

    while (true) {
        cout << "������� ��� �������: ";
        cin >> guess;

        attempts++;

        if (guess == secretNumber) {
            cout << "����������! �� ������� ����� � " << attempts << " �������!" << endl;


            if (attempts == 1) {
                cout << "�� ������� � ������ �������! ��� ������� ������� �� 20!" << endl;
                balance -= bet;
                balance += bet * 20;
            }
            else if (attempts == 2) {
                cout << "�� ������� �� ������ �������! ��� ������� ������� �� 10!" << endl;
                balance -= bet;
                balance += bet * 10;
            }
            else if (attempts == 3) {
                cout << "�� ������� � ������� �������! ��� ������� ������� �� 5!" << endl;
                balance -= bet;
                balance += bet * 5;
            }
            else if (attempts == 4) {
                cout << "�� ������� � ��������� �������! ��� ������� ������� �� 3!" << endl;
                balance -= bet;
                balance += bet * 3;
            }
            else if (attempts == 5) {
                cout << "�� ������� � ����� �������! ��� ������� ������� �� 2!" << endl;
                balance -= bet;
                balance += bet * 2;
            }
            else {
                cout << "�� ������� � ������ ��� ����� �������. ���� ������ �������." << endl;
                balance -= bet;

            }

            break;
        }
        else if (guess < secretNumber) {
            cout << "���������� ����� ������. ���������� ��� ���." << endl;
        }
        else {
            cout << "���������� ����� ������. ���������� ��� ���." << endl;
        }
    }
}

int drawCard() {
    return rand() % 10 + 1;
}

int calculateSum(const vector<int>& hand) {
    int sum = 0;
    int numAces = 0;

    for (int card : hand) {
        if (card == 1) {
            numAces++;
            sum += 11;
        }
        else {
            sum += card;
        }
    }

    while (sum > 21 && numAces > 0) {
        sum -= 10;
        numAces--;
    }

    return sum;
}
void BlackJack(double& balance) {

    double bet;
    do {
        cout << "������� ���� ������ (0 ��� ������ �� ����): ";
        cin >> bet;

        if (bet == 0) {
            return;
        }

        if (bet < 0 || bet > balance) {
            cout << "������������ ������. ����������, ������� ������ �� 0 �� ������ �������� �������." << endl;
        }
    } while (bet < 0 || bet > balance);

    srand(static_cast<unsigned int>(time(0)));

    vector<int> playerHand;
    vector<int> dealerHand;

    playerHand.push_back(drawCard());
    playerHand.push_back(drawCard());

    dealerHand.push_back(drawCard());
    dealerHand.push_back(drawCard());

    cout << "� ��� �� �����: " << playerHand[0] << " � " << playerHand[1] << endl;
    cout << "����� ���������� �����: " << dealerHand[0] << endl;

    while (true) {
        int sum = calculateSum(playerHand);
        cout << "����� ����� ����: " << sum << endl;

        if (sum == 21) {
            cout << "�����������! � ��� ��������!" << endl;
            balance -= bet;
            balance += bet * 10;
            break;
        }
        else if (sum > 21) {
            cout << "� ��� �������. �� ���������." << endl;
            break;
        }

        char choice;
        cout << "������ ����� ��� �����? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            playerHand.push_back(drawCard());
        }
        else {
            break;
        }
    }


    while (calculateSum(dealerHand) < 17) {
        dealerHand.push_back(drawCard());
    }


    int playerSum = calculateSum(playerHand);
    int dealerSum = calculateSum(dealerHand);

    cout << "���� �����: ";
    for (int card : playerHand) {
        cout << card << " ";
    }
    cout << " (�����: " << playerSum << ")" << endl;

    cout << "����� ������: ";
    for (int card : dealerHand) {
        cout << card << " ";
    }
    cout << " (�����: " << dealerSum << ")" << endl;

    if (playerSum > 21 || (dealerSum <= 21 && dealerSum >= playerSum)) {
        cout << "����� �������." << endl;
        balance -= bet;
    }
    else {
        cout << "�� ��������!" << endl;
        balance -= bet;
        balance += bet * 10;
    }

    return;
}

bool flipCoin() {
    return rand() % 2 == 0;
}

void CoinFlip(double& balance) {


    srand(static_cast<unsigned int>(time(0)));

    char userChoice;
    double bet;
    do {
        cout << "������� ���� ������ (0 ��� ������ �� ����): ";
        cin >> bet;

        if (bet == 0) {
            return;
        }

        if (bet < 0 || bet > balance) {
            cout << "������������ ������. ����������, ������� ������ �� 0 �� ������ �������� �������." << endl;
        }
    } while (bet < 0 || bet > balance);


    std::cout << "�������� ������� ������� (1 - ����, 2 - �����): ";
    std::cin >> userChoice;


    if (userChoice == '1') {
        std::cout << "�� ������� ����!" << std::endl;
    }
    else if (userChoice == '2') {
        std::cout << "�� ������� �����!" << std::endl;
    }
    else {
        std::cout << "������������ �����. ����������, ������� '1' ��� '2'." << std::endl;
        return;
    }

    bool result = flipCoin();

    if (result) {
        std::cout << "����� ����!" << std::endl;
    }
    else {
        std::cout << "������ �����!" << std::endl;
    }


    if ((userChoice == '1' && result) || (userChoice == '2' && !result)) {
        std::cout << "�����������, �� �������!" << std::endl;
        balance -= bet;
        balance += bet * 2;
    }
    else {
        std::cout << "���, �� �� �������." << std::endl;
        balance -= bet;
    }

    return;
}


wstring chooseWord() {
    locale::global(locale(""));
    vector<wstring> words = { L"����������������", L"��������", L"�������", L"�����", L"��������", L"�������", L"��������������", L"�������������", L"���������",
        L"����", L"��������", L"����", L"�������", L"������", L"������", L"����������", L"����������", L"����", L"�����", L"��������������", L"������", L"������", L"Dota2"};
    int randomIndex = rand() % words.size();
    return words[randomIndex];
}


wstring displayWord(const wstring& word, const vector<wchar_t>& guessedLetters) {
    wstring displayed;
    for (wchar_t letter : word) {
        if (find(guessedLetters.begin(), guessedLetters.end(), letter) != guessedLetters.end()) {
            displayed += letter;
        }
        else {
            displayed += L'_';
        }
    }
    return displayed;
}


void Hangman(double& balance) {
    SetConsoleCP(1251);
    srand(static_cast<unsigned int>(time(0)));

    wstring secretWord = chooseWord();

    int maxAttempts = 6;
    int attemptsLeft = maxAttempts;
    double bet;
    do {
        cout << "������� ���� ������ (0 ��� ������ �� ����): ";
        cin >> bet;

        if (bet == 0) {
            return;
        }

        if (bet < 0 || bet > balance) {
            cout << "������������ ������. ����������, ������� ������ �� 0 �� ������ �������� �������." << endl;
        }
    } while (bet < 0 || bet > balance);

    vector<wchar_t> guessedLetters;

    wcout << L"����� ���������� � ���� ��������!" << endl;

    while (attemptsLeft > 0) {
        wcout << L"�����: " << displayWord(secretWord, guessedLetters) << endl;
        wcout << L"��������� �����: ";
        for (wchar_t letter : guessedLetters) {
            wcout << letter << L" ";
        }
        wcout << endl;

        wchar_t guess;
        wcout << L"������� �����: ";
        wcin >> guess;

        if (find(guessedLetters.begin(), guessedLetters.end(), guess) != guessedLetters.end()) {
            wcout << L"�� ��� ������� ��� �����. ���������� ������." << endl;
            continue;
        }

        guessedLetters.push_back(guess);

        if (secretWord.find(guess) == wstring::npos) {
            wcout << L"����� ����� ���. �������� �������: " << --attemptsLeft << endl;
        }

        if (displayWord(secretWord, guessedLetters) == secretWord) {
            wcout << L"�����������, �� ������� �����: " << secretWord << endl;
            balance -= bet;
            balance += bet * 3;
            break;
        }
    }

    if (attemptsLeft == 0) {
        wcout << L"�� ���������. ���������� ����� ����: " << secretWord << endl;
        balance -= bet;
    }

    return;
}

double getInitialBalance(const vector<LeaderboardEntry>& leaderboard, const string& username) {
    auto it = find_if(leaderboard.begin(), leaderboard.end(), [&username](const LeaderboardEntry& entry) {
        return entry.username == username;
        });

    if (it != leaderboard.end()) {
        return it->balance;
    }
    else {
        return 500.0;
    }
}

void updateLeaderboard(vector<LeaderboardEntry>& leaderboard, const string& username, double balance) {
    auto it = find_if(leaderboard.begin(), leaderboard.end(), [&username](const LeaderboardEntry& entry) {
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

    sort(leaderboard.begin(), leaderboard.end(), [](const LeaderboardEntry& a, const LeaderboardEntry& b) {
        return a.balance > b.balance;
        });
}

void displayLeaderboard(const vector<LeaderboardEntry>& leaderboard) {
    cout << "������� �������:" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "�������\t\t\t������" << endl;
    cout << "-----------------------------------------" << endl;

    for (const LeaderboardEntry& entry : leaderboard) {
        cout << entry.username << "\t\t\t$" << entry.balance << endl;
    }

    cout << "-----------------------------------------" << endl;
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
