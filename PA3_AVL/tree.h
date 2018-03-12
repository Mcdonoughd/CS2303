//Tree.h By Daniel M. & Surya V.

//check if tree.h has been checked before
#ifndef TREE_H
#define TREE_H

//Define struct node and its fuctions
struct node {
//the key (the word itself)
	char *word;
// the occurance counter
	int count;
// pointers to the leafs of the node
	struct node *left, *right;
// keep track of height from each leaf
	int height;
};
typedef struct node treeNode;
void dispose(treeNode* t);

treeNode* find_min( treeNode *t );
treeNode* find_max( treeNode *t );
//seach through tree
treeNode *findItem(treeNode *, char*);

//add leaf to tree
treeNode *addItem(treeNode *, char*);

//print entire tree inorder
void printTree(treeNode *, char*);

#endif