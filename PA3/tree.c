#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tree.h"

int uniqueWords = 0; //total unique words
int totalWords = 0; //total word count
FILE *output;

/**
 * Find word in tree and return the pointer
 * @param p
 * @param key
 * @return pointer to treeNode of the given word
 */
treeNode *findItem(treeNode *p, char *key) {
	if (p == NULL){
		return NULL; // item not found
	}
	int c = strcmp(key, p->word);
	if (c == 0){
		return p;
	}
	else if (c < 0){
		return findItem(p->left, key);
	}
	else{
		return findItem(p->right, key);
	}
}

/**
 * Add word to the tree, if seen add counter
 * @param p
 * @param w
 * @return
 */
treeNode *addItem(treeNode *p, char *w) {
	//generally add 1 to the total number of words
	totalWords++;
	if (p == NULL) {
		//oh boyo its a unique word; +1 unique!
		uniqueWords++;
		p = malloc(sizeof(treeNode));
		char *c = malloc(strlen(w) + 1);
		p->word = strcpy(c, w);
		p->count = 1;
		p->left = p->right = NULL;
		return p;
	};
	int c = strcmp(w, p->word);
	if (c == 0){
		p->count++;
	}
	else if (c < 0){
		p->left = addItem(p->left, w);
	}
	else{
		p->right = addItem(p->right, w);
	}
	return p;
}


/**
 * print tree into given outputfile
 * @param p
 */
int _printTree(treeNode *p)
{
	if (p == NULL){
		//if null pointer then end of tree
		//exit function
		return 1;
	}
	_printTree(p->left);
	fprintf(output, "%3d:%s\n", p->count, p->word);
	_printTree(p->right);
	return 0;
}
//
/**
 * call _printtree and print total unique words and total words
 * @param p
 * @param file
 */
void printTree(treeNode *p, char * file)
{

	output = fopen(file, "w");

		if(output== NULL){
		fclose(output);
				printf("Error in locating output file!\n");
				exit(0);
				printf("\n\n");
		}

	_printTree(p);
	fprintf(output, "___________________\n");
	fprintf(output, "Total Unique Words: %d\n", uniqueWords);
	fprintf(output, "Total Words: %d", totalWords);
	fclose(output);
}
