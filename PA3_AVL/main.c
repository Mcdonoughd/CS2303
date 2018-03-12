//Main.c by Daniel M. & Surya V.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "tree.h"

treeNode* root;
char* temp;

/**
 * remove punctuation and dashes if not in the middle of a word
 * @param word
 * @return pointer to copy of the word
 */
char* stripPunct(char *word) {
	temp = malloc(strlen(word) + 1);
	int tempCount = 0;
	for (int i = 0; word[i]; i++) {
		char c = word[i];
		if (ispunct(c)) {
			if (c == '\''){
				temp[tempCount] = c;
			}
			else if (c == '-') {
				if(i == 0){
					tempCount--;
				}
				else if (isalpha(word[i - 1]) && isalpha(word[i + 1])){
					temp[tempCount] = c;
				}
				else{
					tempCount--;
				}
			} else{
				tempCount--;
			}
		} else {
			//make word lowercase
			temp[tempCount] = tolower(c);
		}
		tempCount++;
	}

	return temp;

}


//main file
/**
 * Get input args and check if they are valid
 * @param argc
 * @param argv
 * @return end of program
 */
int main(int argc, char *argv[]) {
	if(argc<3){
		printf("Please Initialize arguments!");
		exit(0);
	}
	for (int i = 2; i < argc; i++) {
		FILE *input = fopen(argv[i], "r");
		if(input == NULL) {
			fclose(input);
			printf("Error in locating file!\n");
			exit(0);
			printf("\n\n");
		}
		//assume there will be no words greater then 40 characters
		char* word = (char *) malloc(40);
		//while file is not ended, read the file per word
		while (!feof(input)) {
			fscanf(input, "%s", word);
			word = (char*)stripPunct(word);
			//printf("%s",word);
			if (strcmp(word, ""))
				//add item to the tree
				root = addItem(root, word);
		}
	}
	//print the tree
	printTree(root, argv[1]);
	dispose(root);
	return 0;
}


