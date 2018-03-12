#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include <unistd.h>

FILE *input;
char** initial;
int x, y, gens, print_ = 0, pause_ = 0;
int main(int argc, char *argv[]) {
	if (argc < 4)
		exit(1);
	x = atoi(argv[1]);
	y = atoi(argv[2]);
	gens = atoi(argv[3]);
	input = fopen(argv[4], "r");
	if (argc > 5)
		if (argv[5][0] == 'y')
			print_ = 1;
	if (argc > 6)
		if (argc > 5 && argv[6][0] == 'y')
			pause_ = 1;
	initial = malloc(y * sizeof(char *));
	for (int i = 0; i < y; i++) {
		initial[i] = malloc(x * sizeof(char));
	}
	sizeBoards(y, x);

	char c, last;
	int lines = 0, count = 0, max = 0;
	while (EOF != (c = fgetc(input))) {
		if (c == '\n' && last != '\n')
			++lines;
		last = c;
	}
	rewind(input);

	for (int i = 0; i < lines; i++) {
		while ((c = getc(input)) != '\n') {
			//if (c == '\r')
			//{
			//	printf("Invalid file. No carriage return allowed\n");
			//	exit(1);
			//}
			count++;
		}
		if (count > max)
			max = count;
		count = 0;
	}
	rewind(input);
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			char c = getc(input);
			if (c == '\n') {
				for (int k = j; k < max; k++)
					initial[i][k] = ' ';
				if (j == 0)
					j--;
				else
					break;
			} else if (c == '\r')
				j--;
			else if (c == 'o')
				initial[i][j] = ' ';
			else
				initial[i][j] = c;
		}
	}
	initializeBoard(initial, lines, max);
	for (int i = 0; i < gens; i++) {
		if (print_)
			printBoard(i);
		if (compareSame() || compareOscillation())
			exit(0);
		backupBoard();
		updateBoard();
		if (pause_)
			getchar();
		else
			usleep(500000);
	}
}
