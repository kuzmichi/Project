#include "games.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;

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

int calculateSum(const std::vector<int>& hand) {
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
        L"бром", L"биосфера", L"маяк", L"автомат", L"сессия", L"символ", L"автомобиль", L"гироскутер", L"худи", L"майка", L"алгоритмизация", L"космос", L"солнце", L"Dota2" };
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