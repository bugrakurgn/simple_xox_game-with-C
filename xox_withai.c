#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

char square[10] = { 'o', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
int choice, player, mode;

int checkForWin();
void displayBoard();
void markBoard(char mark);
void computerMove();
//int minimax(char board[10], int isAI);
int minimax(char board[10], int depth, int isAI, int alpha, int beta);

int main()
{
    int gameStatus;
    char mark;

    printf("Choose game mode:\n");
    printf("1. Two Players\n");
    printf("2. Play against AI\n");
    printf("Enter your choice: ");
    scanf("%d", &mode);

    if (mode == 2)
    {
        printf("Computer: O, You: X\n");
        printf("Do you want to play (1)st or (2)nd? ");
        int firstMove;
        scanf("%d", &firstMove);

        if (firstMove == 2)
            player = 2;
        else
            player = 1; 
    }
    else
    {
        player = 1; 
    }

    do
    {
        displayBoard();

        if (mode == 1 || (mode == 2 && player == 1)) 
        {
            printf("Player %d, enter a number: ", player);
            scanf("%d", &choice);

            mark = (player == 1) ? 'X' : 'O';
            markBoard(mark);
        }
        else if (mode == 2 && player == 2) 
        {
            computerMove();
            printf("Computer has made its move.\n");
        }

        gameStatus = checkForWin();

        player = (player % 2) ? 2 : 1; 

    } while (gameStatus == -1);

    displayBoard();

    if (gameStatus == 1)
        printf("==>\aPlayer %d wins!\n", (player == 1) ? 2 : 1);
    else
        printf("==>\aGame draw");

    return 0;
}

int checkForWin()
{
    int returnValue = 0;

    if (square[1] == square[2] && square[2] == square[3])
    {
        returnValue = 1;
    }
    else if (square[4] == square[5] && square[5] == square[6])
        returnValue = 1;

    else if (square[7] == square[8] && square[8] == square[9])
        returnValue = 1;

    else if (square[1] == square[4] && square[4] == square[7])
        returnValue = 1;

    else if (square[2] == square[5] && square[5] == square[8])
        returnValue = 1;

    else if (square[3] == square[6] && square[6] == square[9])
        returnValue = 1;

    else if (square[1] == square[5] && square[5] == square[9])
        returnValue = 1;

    else if (square[3] == square[5] && square[5] == square[7])
        returnValue = 1;

    else if (square[1] != '1' && square[2] != '2' && square[3] != '3' &&
        square[4] != '4' && square[5] != '5' && square[6] != '6' && square[7]
        != '7' && square[8] != '8' && square[9] != '9')
        returnValue = 0;
    else
        returnValue = -1;

    return returnValue;
}

void displayBoard()
{
    system("cls");

    printf("\n\n\tTic Tac Toe\n\n");

    printf("Player 1 (X)  -  Player 2 (O)\n\n\n");

    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", square[1], square[2], square[3]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", square[4], square[5], square[6]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c \n", square[7], square[8], square[9]);

    printf("     |     |     \n\n");
}

void markBoard(char mark)
{
    if (choice == 1 && square[1] == '1')
        square[1] = mark;

    else if (choice == 2 && square[2] == '2')
        square[2] = mark;

    else if (choice == 3 && square[3] == '3')
        square[3] = mark;

    else if (choice == 4 && square[4] == '4')
        square[4] = mark;

    else if (choice == 5 && square[5] == '5')
        square[5] = mark;

    else if (choice == 6 && square[6] == '6')
        square[6] = mark;

    else if (choice == 7 && square[7] == '7')
        square[7] = mark;

    else if (choice == 8 && square[8] == '8')
        square[8] = mark;

    else if (choice == 9 && square[9] == '9')
        square[9] = mark;
    else
    {
        printf("Invalid move ");
        player--; 
        getch();
    }
}


int minimax(char board[10], int depth, int isAI, int alpha, int beta)
{
    int result = checkForWin();
    if (result == 1) return (isAI) ? -10 + depth : 10 - depth; 
    if (result == 0) return 0; 

    if (isAI)
    {
        int bestScore = -1000;
        for (int i = 1; i <= 9; ++i)
        {
            if (board[i] == '0' + i)
            {
                board[i] = 'O';
                int score = minimax(board, depth + 1, 0, alpha, beta);
                board[i] = '0' + i;

                bestScore = (score > bestScore) ? score : bestScore;
                alpha = (alpha > bestScore) ? alpha : bestScore;
                if (beta <= alpha) break;
            }
        }
        return bestScore;
    }
    else
    {
        int bestScore = 1000;
        for (int i = 1; i <= 9; ++i)
        {
            if (board[i] == '0' + i)
            {
                board[i] = 'X';
                int score = minimax(board, depth + 1, 1, alpha, beta);
                board[i] = '0' + i;

                bestScore = (score < bestScore) ? score : bestScore;
                beta = (beta < bestScore) ? beta : bestScore;
                if (beta <= alpha) break;
            }
        }
        return bestScore;
    }
}

void computerMove()
{
    int bestScore = -1000;
    int move = -1;

    for (int i = 1; i <= 9; ++i)
    {
        if (square[i] == '0' + i)
        {
            square[i] = 'O';
            int score = minimax(square, 0, 0, -1000, 1000);
            square[i] = '0' + i;

            if (score > bestScore)
            {
                bestScore = score;
                move = i;
            }
        }
    }
    if (move != -1)
        square[move] = 'O';
}
