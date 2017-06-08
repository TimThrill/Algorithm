/*
 *    Copyright 2015, Jeffrey Chan.
 */

#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_



#include <stdlib.h>
#include <string.h>


struct binTreeNode;
typedef struct binTreeNode binTreeNode_t;

/* Edge link list */
typedef struct edge
{
	int edge;
	struct edge *next;
}Edge_t;

/*
 * Binary tree node data type.
 */
struct binTreeNode {
	int key;
	/* pointer to the value that the node holds */
	void *value;
	/* Balance factor 
	*  balance = left child tree height - right child tree height
	*/
	int balance;
	/* Left and right children subtrees */
	binTreeNode_t *left, *right;
};


typedef struct binTree {
	binTreeNode_t *root;	/* Root of the tree */
	int height;		/* Height of the tree */
}BinTree_t;

/* 
 * Create a tree.
 */
binTreeNode_t* createTreeNode(int key, void *value);


/* 
 * Destroy a tree.
 */
void destroyTree(binTreeNode_t *tree);


/* 
 * Destroy a node
 */
void destroyTreeNode(binTreeNode_t *node);


/*
 * Insert a value.
 * NOTE: Duplicates are allowed.
 */
int insertTreeNode(BinTree_t *pTree, binTreeNode_t *pNewNode);


/*
 * Delete the first node found with value.
 */
int deleteKey(binTreeNode_t **ppTree, int key);


/* 
*	Search a node
*/ 
binTreeNode_t* searchNode(binTreeNode_t *pTree, int key);

binTreeNode_t *search_delete_node(binTreeNode_t *pTree, int key);

/* TODO: Please implement. */
void* allocateValueMemory();

/* TODO: Please implement. */
void freeValueMemory(void *value);

void free_node(binTreeNode_t* node);

int delete_vertex(binTreeNode_t **root, int key);



#endif


