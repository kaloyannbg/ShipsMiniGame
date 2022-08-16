// Имаме 2 играча, които представляват 2 кораба.

// На случаен принцип играта започва от играч 1 или играч 2.

// Всеки играч си има негов кораб. Има 50% шанс при изстрел играча да уцели другият кораб.

// Кораба на всеки играч започва на CORD_NUM0 здраве, което е максималното здраве

// Всяка уцелена координата смъква здравето с 10.

// Всеки кораб има координати от CORD_NUM квадрата [1-CORD_NUM], играта се спечелва тогава,

// когато единия от играчите, унищожи кораба на другия играч!

// Всяка унищожена координата на кораба се отбелязва със звездичка (*)

// Накрая на екрана се изписва победителя и състояниято на двата кораба

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>

#define CORD_HIT_CASE '*'
#define CORD_NUM 9

void printShip(char *playerShip, int cordNum)
{
    for (int i = 0; i < cordNum; i++)
    {
        if ((i % 3) == 0)
        {
            printf("\n");
        }
        printf("[%c]", playerShip[i]);
    }
    printf("\n\n");
}

void hitFreeCoords(char *playerShip, int cordNum)
{
    for (int i = 0; i < cordNum; i++)
    {
        if (playerShip[i] != CORD_HIT_CASE)
        {
            playerShip[i] = CORD_HIT_CASE;
            return;
        }
    }
}

int isWinner(char *playerShip1, char *playerShip2, int cordNum)
{
    int player1LoseCnt = 0;
    int player2LoseCnt = 0;

    for (int i = 0; i < cordNum; i++)
    {
        if (playerShip1[i] == CORD_HIT_CASE)
        {
            ++player1LoseCnt;
        }
        if (playerShip2[i] == CORD_HIT_CASE)
        {
            ++player2LoseCnt;
        }
    }

    if (player1LoseCnt == cordNum)
    {
        return 2; // winner is Player 2
    }
    else if (player2LoseCnt == cordNum)
    {
        return 1; // winner is Player 2
    }
    else
    {
        return 0;
    }
}

int main(int argc, char const *argv[])
{

    srand(time(NULL)); // Initialization, should only be called once.

    int player1Health = 90;
    int player2Health = 90;

    int currentPlayer = 1;

    char player1Ship[CORD_NUM] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    char player2Ship[CORD_NUM] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    // char player2Ship[CORD_NUM] = {CORD_HIT_CASE, CORD_HIT_CASE, CORD_HIT_CASE, CORD_HIT_CASE, CORD_HIT_CASE, CORD_HIT_CASE, CORD_HIT_CASE, CORD_HIT_CASE, CORD_HIT_CASE};
    char getC = 0;
    int hitNow = 0;
    char buffer[1024] = {0};
    while (1)
    {
        system("cls");
        int r = rand() % 2; // Returns a pseudo-random integer between 0 and RAND_MAX.
        getC = 0;
        printf("Player 1 Ship | Health: %d  \n", player1Health);
        printShip(player1Ship, CORD_NUM);

        printf("Player 2 Ship | Health: %d  \n", player2Health);
        printShip(player2Ship, CORD_NUM);

        printf("Player %d its your turn, press ENTER to hit.", currentPlayer);
        while (getC != '\n')
        {
            getC = getchar();
        }

        if (currentPlayer == 1)
        {
            if (r == 0)
            {
                hitFreeCoords(player2Ship, CORD_NUM);
                player2Health -= 10;
                printf(" --- Player 1 you hit player 2! ---");
            }
            else
            {
                printf(" --- Player 1 you miss! :( ---");
            }

            currentPlayer = 2;
        }
        else if (currentPlayer == 2)
        {
            if (r == 0)
            {
                hitFreeCoords(player1Ship, CORD_NUM);
                player1Health -= 10;
                printf(" --- Player 2 you hit player 1! ---");
            }
            else
            {
                printf(" ---  Player 2 you miss! :( ---");
            }

            currentPlayer = 1;
        }

        int winner = isWinner(player1Ship, player2Ship, CORD_NUM);

        if (winner != 0)
        {
            system("cls");
            printf("Player 1 Ship | Health: %d  \n", player1Health);
            printShip(player1Ship, CORD_NUM);

            printf("Player 2 Ship | Health: %d  \n", player2Health);
            printShip(player2Ship, CORD_NUM);
            printf("\n Congratulations! Player %d win! Player %d is lose! \n", winner, currentPlayer);
            break;
        }
        printf("\n\n");
        system("pause");
    }

    return 0;
}
