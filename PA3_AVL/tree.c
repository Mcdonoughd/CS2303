#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tree.h"

int uniqueWords = 0; //total unique words
int totalWords = 0; //total word count
FILE *output;
/**
 * Frees the entire AVL tree
 * @param t
 */
void dispose(treeNode* t)
{
    if( t != NULL )
    {
        dispose( t->left );
        dispose( t->right );
        free( t );
    }
}
/**
 * Finds the lowest character (probably something starting with A)
 * @param t
 * @return
 */
treeNode* find_min( treeNode* t )
{
    if( t == NULL )
        return NULL;
    else if( t->left == NULL )
        return t;
    else
        return find_min( t->left );
}
/**
 *Finds the highest char (probably Z)
 * @param t
 * @return
 */
treeNode* find_max( treeNode* t ){
    if( t != NULL )
        while( t->right != NULL )
            t = t->right;

    return t;
}
/**
 * find maximum of two numbers
 * @param l
 * @param r
 * @return
 */
static int max( int l, int r){
if(l>r){
	return l;
}
else if (r>l){
	return r;
}
else
    return l;
}
/**
 * get height of the tree
 * @param n
 * @return
 */
static int get_height( treeNode* n )
{
    if( n == NULL )
        return -1;
    else
        return n->height;
}

/**
 * perform rotation between and given node and left child
 * @param k2
 * @return
 */
static treeNode* onelr( treeNode* k2 )
{
    treeNode* k1 = NULL;

    k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;

    k2->height = max( get_height( k2->left ), get_height( k2->right ) ) + 1;
    k1->height = max( get_height( k1->left ), k2->height ) + 1;
    return k1; /* new root */
}

/**
 * Do rotation with given node and right child
 * @param k1
 * @return
 */
static treeNode* onerr( treeNode* k1 )
{
    treeNode* k2;

    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;

    k1->height = max( get_height( k1->left ), get_height( k1->right ) ) + 1;
    k2->height = max( get_height( k2->right ), k1->height ) + 1;

    return k2;  /* New root */
}

/**
 * do a left-right double rotation
 * @param k3
 * @return
 */
static treeNode* twolr( treeNode* k3 )
{
    /* Rotate between k1 and k2 */
    k3->left = onerr( k3->left );

    /* Rotate between K3 and k2 */
    return onelr( k3 );
}


/**
 * do right left double rotation
 * @param k1
 * @return
 */
static treeNode* tworr( treeNode* k1 )
{
    /* rotate between K3 and k2 */
    k1->right = onelr( k1->right );

    /* rotate between k1 and k2 */
    return onerr( k1 );
}

/*
    insert a new node into the tree
*/





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
		        if( get_height( p->left ) - get_height( p->right ) == 2 ){
		        	int l = strcmp(w, p->left->word);
		            if( l<0 ){
		                p = onelr( p );
		            }
		            else{
		                p = twolr( p );
		            }
		        }
	}
	else{
		p->right = addItem(p->right, w);
		if( get_height( p->right ) - get_height( p->left ) == 2 ){
				int l = strcmp(w, p->right->word);
		            if( l>0 ){
		                p = onerr( p );
		            }
		            else{
		                p = tworr( p );
		            }
		}
	}
	p->height = max( get_height( p->left ), get_height( p->right ) ) + 1;

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
