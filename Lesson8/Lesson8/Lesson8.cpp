﻿#include <iostream>
#include <random>
#include <stdlib.h>
#include <chrono>

using namespace std;

//======================================================================================

enum TCell : char {
    CROSS = 'X',
    ZERO = '0',
    EMPTY = '_'
};

enum TProgress {
    IN_PROGRESS,
    WON_HUMAN,
    WON_AI,
    DRAW
};

struct TCoord {
    size_t y{ 0U };
    size_t x{ 0U };
};

struct TGame {
    TCell** ppField{ nullptr };
    const size_t SIZE{ 3U };
    TCell human;
    TCell ai;
    TProgress progress{ IN_PROGRESS };
    size_t turn{ 0U }; // четные числа - ход человека, нечетные - компьютера
};

//======================================================================================

inline void clearScr() {
    //system("cls");
    std::cout << "\x1B[2J\x1B[H";
}

int32_t __fastcall getRandomNum(int32_t min, int32_t max) {
    const static auto seed = chrono::system_clock::now().time_since_epoch().count();
    static mt19937_64 generator(seed);
    uniform_int_distribution<int32_t> dis(min, max);
    return dis(generator);
}

void __fastcall initGame(TGame& g) {
    g.ppField = new TCell * [g.SIZE];   // выделяем массив указателей
    for (size_t i = 0; i < g.SIZE; i++) {
        g.ppField[i] = new TCell[g.SIZE];   // строки нашей матрицы
    }

    for (size_t y = 0; y < g.SIZE; y++) {
        for (size_t x = 0; x < g.SIZE; x++) {
            g.ppField[y][x] = EMPTY;
        }
    }

    if (getRandomNum(0, 1000) > 500) {
        g.human = CROSS;
        g.ai = ZERO;
        g.turn = 0;
    }
    else {
        g.human = ZERO;
        g.ai = CROSS;
        g.turn = 1;
    }
}

void __fastcall deinitGame(TGame& g) {
    for (size_t i = 0; i < g.SIZE; i++) {
        delete[] g.ppField[i];
    }
    delete[] g.ppField;
    g.ppField = nullptr;
}

void __fastcall drawGame(const TGame& g) {
    cout << "     ";
    for (size_t x = 0; x < g.SIZE; x++) 
        cout << x + 1 << "   ";
    cout << endl;

    for (size_t y = 0; y < g.SIZE; y++) {
        cout << " " << y + 1 << " | ";
        for (size_t x = 0; x < g.SIZE; x++)
        {
            cout << g.ppField[y][x] << " | ";
        }
        cout << endl;
    }
    cout << endl;

    cout << " Human: " << g.human << endl << " Computer: " << g.ai << endl << endl;
}

void __fastcall congrats(const TGame& g) {
    if (g.progress == WON_HUMAN)
        cout << "Human won! =)" << endl;
    else if (g.progress == WON_AI)
        cout << "Computer won! =/" << endl;
    else if (g.progress == DRAW)
        cout << "Draw! =(" << endl;
}

TProgress getWon(const TGame& g) {
    // проверка победы в строках
    for (size_t y = 0; y < g.SIZE; y++) {       
        if (g.ppField[y][0] == g.ppField[y][1] && g.ppField[y][0] == g.ppField[y][2]) {
            if (g.ppField[y][0] == g.human)
                return WON_HUMAN;

            if (g.ppField[y][0] == g.ai)
                return WON_AI;
        }
    }

    // проверка победы в столбцах
    for (size_t x = 0; x < g.SIZE; x++) {
        if (g.ppField[0][x] == g.ppField[1][x] && g.ppField[0][x] == g.ppField[2][x]) {
            if (g.ppField[0][x] == g.human)
                return WON_HUMAN;

            if (g.ppField[0][x] == g.ai)
                return WON_AI;
        }
    }

    // проверка диагоналей
    if (g.ppField[0][0] == g.ppField[1][1] && g.ppField[0][0] == g.ppField[2][2]) {
        if (g.ppField[1][1] == g.human)
            return WON_HUMAN;

        if (g.ppField[1][1] == g.ai)
            return WON_AI;
    }
    if (g.ppField[2][0] == g.ppField[1][1] && g.ppField[1][1] == g.ppField[0][2]) {
        if (g.ppField[1][1] == g.human)
            return WON_HUMAN;

        if (g.ppField[1][1] == g.ai)
            return WON_AI;
    }

    // может произошла ничья?
    bool draw = true;
    for (size_t y = 0; y < g.SIZE; y++) {
        for (size_t x = 0; x < g.SIZE; x++)
        {
            if (g.ppField[y][x] == EMPTY) {
                draw = false;
                break;
           }
        }
        if (!draw)
            break;
    }
    if (draw)
        return DRAW;

    return IN_PROGRESS;
}

TCoord getHumanCoord(const TGame& g) {
    TCoord c;
    do {
        cout << "Enter X (1..3): ";
        cin >> c.x;
        cout << "Enter Y (1..3): ";
        cin >> c.y;

        c.x--; // 0..2
        c.y--;
    } while (c.x > 2 || c.y > 2 || g.ppField[c.y][c.x] != EMPTY);

    return c;
}

TCoord getAiCoord(TGame& g) {
    // 1. PRE WIN SITUATION
    for (size_t y = 0; y < g.SIZE; y++) {
        for (size_t x = 0; x < g.SIZE; x++)
        {
            if (g.ppField[y][x] == EMPTY) {
                g.ppField[y][x] = g.ai;
                if (getWon(g) == WON_AI) {
                    g.ppField[y][x] = EMPTY;
                    return { y, x }; // компьютер выигрывает сам
                }
                g.ppField[y][x] = EMPTY;
            }
        }
    }

    // 2. PRE FAIL SITATION
    for (size_t y = 0; y < g.SIZE; y++) {
        for (size_t x = 0; x < g.SIZE; x++)
        {
            if (g.ppField[y][x] == EMPTY) {
                g.ppField[y][x] = g.human;
                if (getWon(g) == WON_HUMAN) {
                    g.ppField[y][x] = EMPTY;
                    return { y, x };  // мешаем человеку выиграть
                }
                g.ppField[y][x] = EMPTY;
            }
        }
    }

    // 3. По приоритетам + ранд
    if (g.ppField[1][1] == EMPTY)
        return { 1, 1 };

    // проверка углов
    TCoord buf[4];
    size_t num{ 0 };
    if (g.ppField[0][0] = EMPTY) {
        buf[num++] = { 0, 0 };
    }
    if (g.ppField[2][2] = EMPTY) {
        buf[num++] = { 2, 2 };
    }
    if (g.ppField[0][2] = EMPTY) {
        buf[num++] = { 0, 2 };
    }
    if (g.ppField[2][0] = EMPTY) {
        buf[num++] = { 2, 0 };
    }
    if (num > 0) {
        const size_t index = getRandomNum(0, 1000) % num;
        return buf[index]; // возвращаем случайный угол из найденых свободных свободных углов
    }

    // проверка не углов
    num = 0;
    if (g.ppField[0][1] = EMPTY) {
        buf[num++] = { 0, 1 };
    }
    if (g.ppField[2][1] = EMPTY) {
        buf[num++] = { 2, 1 };
    }
    if (g.ppField[1][0] = EMPTY) {
        buf[num++] = { 1, 0 };
    }
    if (g.ppField[1][2] = EMPTY) {
        buf[num++] = { 1, 2 };
    }
    if (num > 0) {
        const size_t index = getRandomNum(0, 1000) % num;
        return buf[index]; // возвращаем случайный НЕ угол из найденых свободных свободных углов
    }
}

//=================================================================================

int main()
{
    TGame g;
    initGame(g);
    clearScr();
    drawGame(g);

    do {
        if (g.turn % 2 == 0) {
            // ход человека
            TCoord c = getHumanCoord(g);
            g.ppField[c.y][c.x] = g.human;
        }
        else {
            // ход компьютера
            TCoord c = getAiCoord(g);
            g.ppField[c.y][c.x] = g.ai;
        }

        g.turn++;
        clearScr();
        drawGame(g);
        g.progress = getWon(g);
    } while (g.progress == IN_PROGRESS);

    congrats(g);
    deinitGame(g);
    return 0;
}

