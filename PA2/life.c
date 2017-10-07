//Game of Life By Daniel McDonough 9/15/17
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 4000
/* dimensions of the screen */

/* set everthing to zero */
void initialize_board (int x, int y, int board[][x]) {
	int	i, j;

	for (i=0; i<y; i++){
		for (j=0; j<x; j++){
			board[i][j] = 0;
			//printf("%d",board[i][j]);
		}
		//printf("\n");
	}
}
//print the board
void printboard (int x,int y,int board[][x]) {
	int	i, j;
	/* for each row */
	for (j=0; j<y; j++) {

		/* print each column position... */

		for (i=0; i<x; i++) {
			printf ("%d", board[j][i]);
		}

		/* followed by a carriage return */
		printf ("\n");
	}
	printf ("\n\n");
}

/* add to a width index, wrapping around like a cylinder */
int xadd (int x,int i, int a) {
	i += a;
	while (i < 0) i += x;
	while (i >= x) i -= x;
	return i;
}

//is input y?
int NorY(char input){
	if(input != 'y' || input != 'Y'){
		return 0;
	}
	return 1;
}

/* add to a height index, wrapping around */
int yadd (int i, int a,int y) {
	i += a;
	while (i < 0) i += y;
	while (i >= y) i -= y;
	return i;
}

/* return the number of on cells adjacent to the i,j cell */
int adjacent_to (int x, int y,int board[][x], int i, int j) {
	int	k, l, count;

	count = 0;

	/* go around the cell */

	for (k=-1; k<=1; k++){
		for (l=-1; l<=1; l++){

		}
	}

		/* only count if at least one of k,l isn't zero */

		if (k || l){
			if (board[yadd(j,l,y)][xadd(x,i,k)]){
				count++;
			}
		}
	return count;
}
//play the game
int playboard (int x,int y,int board[][x]) {
	/*
	1.STASIS : If, for a given cell, the number of on neighbours is
	exactly two, the cell maintains its status quo into the next
	generation. If the cell is on, it stays on, if it is off, it stays off.

	2.GROWTH : If the number of on neighbours is exactly three, the cell
	will be on in the next generation. This is regardless of the cell's current state.

	3.DEATH : If the number of on neighbours is 0, 1, 4-8, the cell will
	be off in the next generation.
	 */
	int	i, j, a, newboard[y][x];

	/* for each cell, apply the rules of Life */

	for (i=0; i<y; i++){
		for (j=0; j<x; j++) {
			a = adjacent_to (x,y,board, i, j);
			if (a == 2) newboard[i][j] = board[i][j];
			if (a == 3) newboard[i][j] = 1;
			if (a < 2) newboard[i][j] = 0;
			if (a > 3) newboard[i][j] = 0;
		}
	}
	//Check if two arrays are the same
	int q =0;
	for (i=0; i<y; i++){
		for (j=0; j<x; j++) {
			if(board[i][j] == newboard[i][j]){
				q++;
			}
		}
	}
	if(q == (x*y)){
		//if all cells are same stop
		//print final board
		printboard(x,y,board);
		printf("Game Terminated \n");
		exit(0);
	}

	/* copy the new board back into the old board */

	for (i=0; i<y; i++){
		for (j=0; j<x; j++) {
			board[i][j] = newboard[i][j];
		}
	}
	return 0;
}

/* get the number of lines input in the file */
int get_numlines(char *filename) {
  char buf[MAX] = {0};
  FILE *file;

  char line_val[MAX] = {0};
  int line_len = -1;
  int line_num = -1;
  int cur_line = 1;

  file = fopen(filename, "r");
	if(file == NULL) {
		fclose(file);
		printf("Error in opening file!\n");
		exit(0);
		printf("\n\n");
	}

  /* Go until the end of the file. */
  while(fgets(buf, MAX, file) != NULL) {
    int len_tmp = strlen(buf) - 1; /* -1 because of the newline. */

    /* Just kill the newline with an extra '\0'. */
    if(buf[len_tmp] == '\n')
      buf[len_tmp] = '\0';

    /* We've found a longer one! */
    if(line_len < len_tmp) {
      strncpy(line_val, buf, len_tmp + 1);
      line_len = len_tmp;
      line_num = cur_line;
    }

    /* Increment line counter. */
    cur_line++;
    /*printf("%s", buf);*/
  }

  /* Done reading, so close the file. */


  /* We never found a line... */
  if(line_num < 1) {
    fprintf(stderr, "Got no lines from file %s.\n", filename);
    exit(0);
  }
  return line_num;
}
/* read a file into the life board */

void read_file (int x,int y, int board[][x], char *name) {
	FILE	*f;
	int	i, j;
	char	s[MAX];//4000 is a buffer number and the max area a board can have
	int linelength = get_numlines(name);
	f = fopen (name, "r");
	rewind(f);
	if(f == NULL) {
		fclose(f);
		printf("Error in opening file!\n");
		exit(0);
		printf("\n\n");
	}
	//int	i, j;

	for (j=0; j<linelength; j++) {

		/* get a string */

		fgets (s, MAX, f);
		//printf("%s",s);
		/* copy the string to the life board */

		for (i=0; i<x; i++) {
			if(s[i]=='x'){
				board[j][i] = 1;
			}
		}
	}
	fclose (f);
}

/* main program */

int main (int argc, char *argv[]) {
	if(argc < 4){
		printf("Please Initialize Arguments!\n");
		return 1;
	}
	else{
		int x = atoi(argv[1]);
		int y = atoi(argv[2]);
		int gens = atoi(argv[3]);
		char print = 'n';
		char pause = 'n';
		if(argc == 6){
			if(NorY(print)){
				printf("Please Input Valid Print Argument!\n");
				return 1;
			}
			print =  (char)*argv[5];
			//printf("%c\n",pause);
		}
		else if (argc >= 7){
			print = *argv[5];
			pause = *argv[6];

			if(NorY(print)){
				printf("Please Input Valid Print Argument!\n");
				return 1;
			}
			if(NorY(pause)){
				printf("Please Input Valid Pause Argument!\n");
				return 1;
			}
		}
		//printf("Proper Arguments!\n");
		int	board[y][x];
		int i;
		//initialize board
		initialize_board (x,y,board);
		//input initial file into board
		read_file (x,y,board,argv[4]);
		printboard(x,y,board);
//print for so many gens
		for (i=0; i<gens; i++) {
			if(NorY(print)){
				printboard(x,y,board);
				printf("\n");
			}
			playboard(x,y,board);
		}
		//print final board
		printboard(x,y,board);
		return 0;
	}
}
