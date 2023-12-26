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
        L"����", L"��������", L"����", L"�������", L"������", L"������", L"����������", L"����������", L"����", L"�����", L"��������������", L"������", L"������", L"Dota2" };
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