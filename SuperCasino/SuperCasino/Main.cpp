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
        cout << "Ошибка сохранения таблицы лидеров." << endl;
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
        cout << "Ошибка загрузки таблицы лидеров." << endl;
    }
}

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

int generateRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void playGuessNumber(double& balance) {
    const int minNumber = 1;
    const int maxNumber = 100;

    int secretNumber = generateRandomNumber(minNumber, maxNumber);

    cout << "Добро пожаловать в игру 'Угадай число'!" << endl;
    cout << "Я загадал число от " << minNumber << " до " << maxNumber << ". Попробуйте угадать!" << endl;

    int attempts = 0;
    int guess;
    double bet;
    do {
        cout << "Введите вашу ставку (0 для выхода из игры): ";
        cin >> bet;

        if (bet == 0) {
            return;
        }

        if (bet < 0 || bet > balance) {
            cout << "Недопустимая ставка. Пожалуйста, введите ставку от 0 до вашего текущего баланса." << endl;
        }
             } while (bet < 0 || bet > balance);
 

    while (true) {
        cout << "Введите ваш вариант: ";
        cin >> guess;

        attempts++;

        if (guess == secretNumber) {
            cout << "Поздравляю! Вы угадали число с " << attempts << " попытки!" << endl;


            if (attempts == 1) {
                cout << "Вы угадали с первой попытки! Ваш выигрыш умножен на 20!" << endl;
                balance -= bet;
                balance += bet * 20;
            }
            else if (attempts == 2) {
                cout << "Вы угадали со второй попытки! Ваш выигрыш умножен на 10!" << endl;
                balance -= bet;
                balance += bet * 10;
            }
            else if (attempts == 3) {
                cout << "Вы угадали с третьей попытки! Ваш выигрыш умножен на 5!" << endl;
                balance -= bet;
                balance += bet * 5;
            }
            else if (attempts == 4) {
                cout << "Вы угадали с четвертой попытки! Ваш выигрыш умножен на 3!" << endl;
                balance -= bet;
                balance += bet * 3;
            }
            else if (attempts == 5) {
                cout << "Вы угадали с пятой попытки! Ваш выигрыш умножен на 2!" << endl;
                balance -= bet;
                balance += bet * 2;
            }
            else {
                cout << "Вы угадали с шестой или более попытки. Ваша ставка сгорает." << endl;
                balance -= bet;

            }

            break;
        }
        else if (guess < secretNumber) {
            cout << "Загаданное число больше. Попробуйте еще раз." << endl;
        }
        else {
            cout << "Загаданное число меньше. Попробуйте еще раз." << endl;
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
        cout << "Введите вашу ставку (0 для выхода из игры): ";
        cin >> bet;

        if (bet == 0) {
            return;
        }

        if (bet < 0 || bet > balance) {
            cout << "Недопустимая ставка. Пожалуйста, введите ставку от 0 до вашего текущего баланса." << endl;
        }
    } while (bet < 0 || bet > balance);

    srand(static_cast<unsigned int>(time(0)));

    vector<int> playerHand;
    vector<int> dealerHand;

    playerHand.push_back(drawCard());
    playerHand.push_back(drawCard());

    dealerHand.push_back(drawCard());
    dealerHand.push_back(drawCard());

    cout << "У вас на руках: " << playerHand[0] << " и " << playerHand[1] << endl;
    cout << "Дилер показывает карту: " << dealerHand[0] << endl;

    while (true) {
        int sum = calculateSum(playerHand);
        cout << "Сумма ваших карт: " << sum << endl;

        if (sum == 21) {
            cout << "Поздравляем! У вас блэкджек!" << endl;
            balance -= bet;
            balance += bet * 10;
            break;
        }
        else if (sum > 21) {
            cout << "У вас перебор. Вы проиграли." << endl;
            break;
        }

        char choice;
        cout << "Хотите взять еще карту? (y/n): ";
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

    cout << "Ваши карты: ";
    for (int card : playerHand) {
        cout << card << " ";
    }
    cout << " (Сумма: " << playerSum << ")" << endl;

    cout << "Карты дилера: ";
    for (int card : dealerHand) {
        cout << card << " ";
    }
    cout << " (Сумма: " << dealerSum << ")" << endl;

    if (playerSum > 21 || (dealerSum <= 21 && dealerSum >= playerSum)) {
        cout << "Дилер выиграл." << endl;
        balance -= bet;
    }
    else {
        cout << "Вы выиграли!" << endl;
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
        cout << "Введите вашу ставку (0 для выхода из игры): ";
        cin >> bet;

        if (bet == 0) {
            return;
        }

        if (bet < 0 || bet > balance) {
            cout << "Недопустимая ставка. Пожалуйста, введите ставку от 0 до вашего текущего баланса." << endl;
        }
    } while (bet < 0 || bet > balance);


    std::cout << "Выберите сторону монетки (1 - орел, 2 - решка): ";
    std::cin >> userChoice;


    if (userChoice == '1') {
        std::cout << "Вы выбрали орла!" << std::endl;
    }
    else if (userChoice == '2') {
        std::cout << "Вы выбрали решку!" << std::endl;
    }
    else {
        std::cout << "Некорректный выбор. Пожалуйста, введите '1' или '2'." << std::endl;
        return;
    }

    bool result = flipCoin();

    if (result) {
        std::cout << "Выпал орел!" << std::endl;
    }
    else {
        std::cout << "Выпала решка!" << std::endl;
    }


    if ((userChoice == '1' && result) || (userChoice == '2' && !result)) {
        std::cout << "Поздравляем, вы угадали!" << std::endl;
        balance -= bet;
        balance += bet * 2;
    }
    else {
        std::cout << "Увы, вы не угадали." << std::endl;
        balance -= bet;
    }

    return;
}


wstring chooseWord() {
    locale::global(locale(""));
    vector<wstring> words = { L"программирование", L"виселица", L"серебро", L"слово", L"алгоритм", L"техника", L"турбогенератор", L"пневмосклероз", L"кинофильм",
        L"бром", L"биосфера", L"маяк", L"автомат", L"сессия", L"символ", L"автомобиль", L"гироскутер", L"худи", L"майка", L"алгоритмизация", L"космос", L"солнце", L"Dota2"};
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
        cout << "Введите вашу ставку (0 для выхода из игры): ";
        cin >> bet;

        if (bet == 0) {
            return;
        }

        if (bet < 0 || bet > balance) {
            cout << "Недопустимая ставка. Пожалуйста, введите ставку от 0 до вашего текущего баланса." << endl;
        }
    } while (bet < 0 || bet > balance);

    vector<wchar_t> guessedLetters;

    wcout << L"Добро пожаловать в игру Виселица!" << endl;

    while (attemptsLeft > 0) {
        wcout << L"Слово: " << displayWord(secretWord, guessedLetters) << endl;
        wcout << L"Угаданные буквы: ";
        for (wchar_t letter : guessedLetters) {
            wcout << letter << L" ";
        }
        wcout << endl;

        wchar_t guess;
        wcout << L"Введите букву: ";
        wcin >> guess;

        if (find(guessedLetters.begin(), guessedLetters.end(), guess) != guessedLetters.end()) {
            wcout << L"Вы уже вводили эту букву. Попробуйте другую." << endl;
            continue;
        }

        guessedLetters.push_back(guess);

        if (secretWord.find(guess) == wstring::npos) {
            wcout << L"Такой буквы нет. Осталось попыток: " << --attemptsLeft << endl;
        }

        if (displayWord(secretWord, guessedLetters) == secretWord) {
            wcout << L"Поздравляем, вы угадали слово: " << secretWord << endl;
            balance -= bet;
            balance += bet * 3;
            break;
        }
    }

    if (attemptsLeft == 0) {
        wcout << L"Вы проиграли. Загаданное слово было: " << secretWord << endl;
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
    cout << "Таблица лидеров:" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Никнейм\t\t\tБаланс" << endl;
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
