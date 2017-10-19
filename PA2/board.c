#include <stdio.h>
#include <stdlib.h>
#include "board.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char** B;
char** B1;
char** B2;
int rows, cols;
void sizeBoards(int y, int x) {
	rows = y;
	cols = x;
	B = malloc(rows * sizeof(char *));
	for (int i = 0; i < rows; i++)
		B[i] = malloc(cols * sizeof(char));
	for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
			B[i][j] = ' ';

	B1 = malloc(rows * sizeof(char *));
	for (int i = 0; i < rows; i++)
		B1[i] = malloc(cols * sizeof(char));
	B2 = malloc(rows * sizeof(char *));
	for (int i = 0; i < rows; i++)
		B2[i] = malloc(cols * sizeof(char));
}
void initializeBoard(char** initial, int rows_, int cols_) {

	int yOffset = rows / 2 - rows_ / 2;
	int xOffset = cols / 2 - cols_ / 2;
	for (int i = 0; i < rows_; i++)
		for (int j = 0; j < cols_; j++)
			if (initial[i][j] == ' ' || initial[i][j] == 'x')
				B[i + yOffset][j + xOffset] = initial[i][j];
}

void backupBoard() {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			B2[i][j] = B1[i][j];

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			B1[i][j] = B[i][j];
}

int compareSame() {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (!(B1[i][j] == B[i][j])) {
				return 0;
			}
	return 1;
}

int compareOscillation() {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (!(B2[i][j] == B[i][j])) {
				return 0;
			}
	return 1;
}
void updateBoard() {
	char tempBoard[rows][cols];
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (getNeighbors(i, j) < 2 || getNeighbors(i, j) > 3)
				tempBoard[i][j] = ' ';
			else if (getNeighbors(i, j) == 3)
				tempBoard[i][j] = 'x';
			else
				tempBoard[i][j] = B[i][j];

		}
	}
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			B[i][j] = tempBoard[i][j];
}

int getNeighbors(int y, int x) {
	int sum = 0;
	//Check Left
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0)
				continue;

			if (!(x + j < 0 || x + j > cols - 1 || y + i < 0 || y + i > rows - 1))
				sum += B[y + i][x + j] == 'x';
		}
	}

	return sum;
}
void printBoard(int gen) {
	//printf("\e[1;1H\e[2J"); //clear output
	printf("Generation: %d\n", gen);
    for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
		{
			if (B[i][j] == 'x')
				printf(ANSI_COLOR_RED "x "  ANSI_COLOR_RESET);
			else
				printf("%c ", B[i][j]);
		}
		printf("\n");
	}
	printf("\033[%dA \r", rows+1);
}
