
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

    cout << "Äîáðî ïîæàëîâàòü â èãðó 'Óãàäàé ÷èñëî'!" << endl;
    cout << "ß çàãàäàë ÷èñëî îò " << minNumber << " äî " << maxNumber << ". Ïîïðîáóéòå óãàäàòü!" << endl;

    int attempts = 0;
    int guess;
    double bet;
    do {
        cout << "Ââåäèòå âàøó ñòàâêó (0 äëÿ âûõîäà èç èãðû): ";
        cin >> bet;

        if (bet == 0) {
            return;
        }

        if (bet < 0 || bet > balance) {
            cout << "Íåäîïóñòèìàÿ ñòàâêà. Ïîæàëóéñòà, ââåäèòå ñòàâêó îò 0 äî âàøåãî òåêóùåãî áàëàíñà." << endl;
        }
    } while (bet < 0 || bet > balance);


    while (true) {
        cout << "Ââåäèòå âàø âàðèàíò: ";
        cin >> guess;

        attempts++;

        if (guess == secretNumber) {
            cout << "Ïîçäðàâëÿþ! Âû óãàäàëè ÷èñëî ñ " << attempts << " ïîïûòêè!" << endl;


            if (attempts == 1) {
                cout << "Âû óãàäàëè ñ ïåðâîé ïîïûòêè! Âàø âûèãðûø óìíîæåí íà 20!" << endl;
                balance -= bet;
                balance += bet * 20;
            }
            else if (attempts == 2) {
                cout << "Âû óãàäàëè ñî âòîðîé ïîïûòêè! Âàø âûèãðûø óìíîæåí íà 10!" << endl;
                balance -= bet;
                balance += bet * 10;
            }
            else if (attempts == 3) {
                cout << "Âû óãàäàëè ñ òðåòüåé ïîïûòêè! Âàø âûèãðûø óìíîæåí íà 5!" << endl;
                balance -= bet;
                balance += bet * 5;
            }
            else if (attempts == 4) {
                cout << "Âû óãàäàëè ñ ÷åòâåðòîé ïîïûòêè! Âàø âûèãðûø óìíîæåí íà 3!" << endl;
                balance -= bet;
                balance += bet * 3;
            }
            else if (attempts == 5) {
                cout << "Âû óãàäàëè ñ ïÿòîé ïîïûòêè! Âàø âûèãðûø óìíîæåí íà 2!" << endl;
                balance -= bet;
                balance += bet * 2;
            }
            else {
                cout << "Âû óãàäàëè ñ øåñòîé èëè áîëåå ïîïûòêè. Âàøà ñòàâêà ñãîðàåò." << endl;
                balance -= bet;

            }

            break;
        }
        else if (guess < secretNumber) {
            cout << "Çàãàäàííîå ÷èñëî áîëüøå. Ïîïðîáóéòå åùå ðàç." << endl;
        }
        else {
            cout << "Çàãàäàííîå ÷èñëî ìåíüøå. Ïîïðîáóéòå åùå ðàç." << endl;
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
        cout << "Ââåäèòå âàøó ñòàâêó (0 äëÿ âûõîäà èç èãðû): ";
        cin >> bet;

        if (bet == 0) {
            return;
        }

        if (bet < 0 || bet > balance) {
            cout << "Íåäîïóñòèìàÿ ñòàâêà. Ïîæàëóéñòà, ââåäèòå ñòàâêó îò 0 äî âàøåãî òåêóùåãî áàëàíñà." << endl;
        }
    } while (bet < 0 || bet > balance);

    srand(static_cast<unsigned int>(time(0)));

    vector<int> playerHand;
    vector<int> dealerHand;

    playerHand.push_back(drawCard());
    playerHand.push_back(drawCard());

    dealerHand.push_back(drawCard());
    dealerHand.push_back(drawCard());

    cout << "Ó âàñ íà ðóêàõ: " << playerHand[0] << " è " << playerHand[1] << endl;
    cout << "Äèëåð ïîêàçûâàåò êàðòó: " << dealerHand[0] << endl;

    while (true) {
        int sum = calculateSum(playerHand);
        cout << "Ñóììà âàøèõ êàðò: " << sum << endl;

        if (sum == 21) {
            cout << "Ïîçäðàâëÿåì! Ó âàñ áëýêäæåê!" << endl;
            balance -= bet;
            balance += bet * 10;
            break;
        }
        else if (sum > 21) {
            cout << "Ó âàñ ïåðåáîð. Âû ïðîèãðàëè." << endl;
            break;
        }

        char choice;
        cout << "Õîòèòå âçÿòü åùå êàðòó? (y/n): ";
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

    cout << "Âàøè êàðòû: ";
    for (int card : playerHand) {
        cout << card << " ";
    }
    cout << " (Ñóììà: " << playerSum << ")" << endl;

    cout << "Êàðòû äèëåðà: ";
    for (int card : dealerHand) {
        cout << card << " ";
    }
    cout << " (Ñóììà: " << dealerSum << ")" << endl;

    if (playerSum > 21 || (dealerSum <= 21 && dealerSum >= playerSum)) {
        cout << "Äèëåð âûèãðàë." << endl;
        balance -= bet;
    }
    else {
        cout << "Âû âûèãðàëè!" << endl;
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
        cout << "Ââåäèòå âàøó ñòàâêó (0 äëÿ âûõîäà èç èãðû): ";
        cin >> bet;

        if (bet == 0) {
            return;
        }

        if (bet < 0 || bet > balance) {
            cout << "Íåäîïóñòèìàÿ ñòàâêà. Ïîæàëóéñòà, ââåäèòå ñòàâêó îò 0 äî âàøåãî òåêóùåãî áàëàíñà." << endl;
        }
    } while (bet < 0 || bet > balance);


    std::cout << "Âûáåðèòå ñòîðîíó ìîíåòêè (1 - îðåë, 2 - ðåøêà): ";
    std::cin >> userChoice;


    if (userChoice == '1') {
        std::cout << "Âû âûáðàëè îðëà!" << std::endl;
    }
    else if (userChoice == '2') {
        std::cout << "Âû âûáðàëè ðåøêó!" << std::endl;
    }
    else {
        std::cout << "Íåêîððåêòíûé âûáîð. Ïîæàëóéñòà, ââåäèòå '1' èëè '2'." << std::endl;
        return;
    }

    bool result = flipCoin();

    if (result) {
        std::cout << "Âûïàë îðåë!" << std::endl;
    }
    else {
        std::cout << "Âûïàëà ðåøêà!" << std::endl;
    }


    if ((userChoice == '1' && result) || (userChoice == '2' && !result)) {
        std::cout << "Ïîçäðàâëÿåì, âû óãàäàëè!" << std::endl;
        balance -= bet;
        balance += bet * 2;
    }
    else {
        std::cout << "Óâû, âû íå óãàäàëè." << std::endl;
        balance -= bet;
    }

    return;
}

wstring chooseWord() {
    locale::global(locale(""));
    vector<wstring> words = { L"ïðîãðàììèðîâàíèå", L"âèñåëèöà", L"ñåðåáðî", L"ñëîâî", L"àëãîðèòì", L"òåõíèêà", L"òóðáîãåíåðàòîð", L"ïíåâìîñêëåðîç", L"êèíîôèëüì",
        L"áðîì", L"áèîñôåðà", L"ìàÿê", L"àâòîìàò", L"ñåññèÿ", L"ñèìâîë", L"àâòîìîáèëü", L"ãèðîñêóòåð", L"õóäè", L"ìàéêà", L"àëãîðèòìèçàöèÿ", L"êîñìîñ", L"ñîëíöå", L"Dota2" };
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
        cout << "Ââåäèòå âàøó ñòàâêó (0 äëÿ âûõîäà èç èãðû): ";
        cin >> bet;

        if (bet == 0) {
            return;
        }

        if (bet < 0 || bet > balance) {
            cout << "Íåäîïóñòèìàÿ ñòàâêà. Ïîæàëóéñòà, ââåäèòå ñòàâêó îò 0 äî âàøåãî òåêóùåãî áàëàíñà." << endl;
        }
    } while (bet < 0 || bet > balance);

    vector<wchar_t> guessedLetters;

    wcout << L"Äîáðî ïîæàëîâàòü â èãðó Âèñåëèöà!" << endl;

    while (attemptsLeft > 0) {
        wcout << L"Ñëîâî: " << displayWord(secretWord, guessedLetters) << endl;
        wcout << L"Óãàäàííûå áóêâû: ";
        for (wchar_t letter : guessedLetters) {
            wcout << letter << L" ";
        }
        wcout << endl;

        wchar_t guess;
        wcout << L"Ââåäèòå áóêâó: ";
        wcin >> guess;

        if (find(guessedLetters.begin(), guessedLetters.end(), guess) != guessedLetters.end()) {
            wcout << L"Âû óæå ââîäèëè ýòó áóêâó. Ïîïðîáóéòå äðóãóþ." << endl;
            continue;
        }

        guessedLetters.push_back(guess);

        if (secretWord.find(guess) == wstring::npos) {
            wcout << L"Òàêîé áóêâû íåò. Îñòàëîñü ïîïûòîê: " << --attemptsLeft << endl;
        }

        if (displayWord(secretWord, guessedLetters) == secretWord) {
            wcout << L"Ïîçäðàâëÿåì, âû óãàäàëè ñëîâî: " << secretWord << endl;
            balance -= bet;
            balance += bet * 3;
            break;
        }
    }

    if (attemptsLeft == 0) {
        wcout << L"Âû ïðîèãðàëè. Çàãàäàííîå ñëîâî áûëî: " << secretWord << endl;
        balance -= bet;
    }

    return;
}
