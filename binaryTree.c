/*
 *    Copyright 2015, Jeffrey Chan.
 */

#include <stdio.h>
#include <stdlib.h>
#include "binaryTree.h"
#include "commonDefs.h"
#include "memoryUtil.h"


/* ******************************************************************** */




/* ******************************************************************** */

binTreeNode_t* createTreeNode(int key, void *value)
{
	binTreeNode_t *pNode = NULL;
	
	pNode = (binTreeNode_t*) safeMalloc(sizeof(binTreeNode_t));
	
	pNode->key = key;
	pNode->value = value;
	pNode->left = NULL;
	pNode->right = NULL;
	
	return pNode;
} /* end of createNode() */


/* 
 * Destroy a tree.
 */
void destroyTree(binTreeNode_t *pTree)
{
	binTreeNode_t *pLeftChild = pTree->left, *pRightChild = pTree->right;
	
	if (pLeftChild != NULL) {
		destroyTree(pLeftChild);
	}
	
	if (pRightChild != NULL) {
		destroyTree(pRightChild);
	}
	
	destroyTreeNode(pTree);
	pTree = NULL;
} /* end of destroyTree() */


/* 
 * Destroy a node
 */
void destroyTreeNode(binTreeNode_t *pNode)
{
	freeValueMemory(pNode->value);
	/* Implement me!  Please determine the size of deallocated pNode->value */
	/* safeFree(pNode, sizeof(X)); */
} /* end of destroyNode() */

/* For balance the RR situation */
binTreeNode_t* rotate_RR(binTreeNode_t* rTree)
{
	/* Repair link */
	binTreeNode_t* tmp = rTree->right;
	rTree->right = tmp->left;
	tmp->left = rTree;
	
	/* Repair balance */
	if(tmp->balance == -1)
	{
		rTree->balance = 0;
		tmp->balance = 0;
	}
	else
	{
		rTree->balance = -1;
		tmp->balance = 1;
	}
	return tmp;
}

/* For balance the RL situation */
binTreeNode_t* rotate_RL(binTreeNode_t* rTree)
{
	/* Make a right rotation */
	binTreeNode_t *tmp = rTree->right->left;
	rTree->right->left = tmp->right;
	tmp->right = rTree->right;
	rTree->right = tmp;
	
	/* Make a left rotation */
	rTree->right = tmp->left;
	tmp->left = rTree;
	
	/* Repair balance */
	if(tmp->balance == 0)
	{
		rTree->balance = 0;
		tmp->right->balance = 0;
		tmp->balance = 0;
	}
	else if(tmp->balance < 0)
	{
		rTree->balance = 1;
		tmp->right->balance = 0;
		tmp->balance = 0;
	}
	else
	{
		rTree->balance = 0;
		tmp->right->balance = -1;
		tmp->balance = 0;
	}
	
	return tmp; 
}

/* For balance the LL situation */
binTreeNode_t* rotate_LL(binTreeNode_t* lTree)
{
	/* Repair link */
	binTreeNode_t* tmp = lTree->left;
	lTree->left = tmp->right;
	tmp->right = lTree;
	
	/* Repair balance */
	if(tmp->balance == 1)
	{
		lTree->balance = 0;
		tmp->balance = 0;
	}
	else
	{
		lTree->balance = 1;
		tmp->balance = -1;
	}
	return tmp; 
}

/* For balance the LR situation */
binTreeNode_t* rotate_LR(binTreeNode_t* lTree)
{
	/* Make a left rotation */
	binTreeNode_t *tmp = lTree->left->right;
	lTree->left->right = tmp->left;
	tmp->left = lTree->left;
	lTree->left = tmp;
	
	/* Make a right rotation */
	lTree->left = tmp->right;
	tmp->right = lTree;
	
	/* Repair balance */
	if(tmp->balance == 0)
	{
		lTree->balance = 0;
		tmp->left->balance = 0;
		tmp->balance = 0;
	}
	else if(tmp->balance < 0)
	{
		lTree->balance = 0;
		tmp->left->balance = 1;
		tmp->balance = 0;
	}
	else
	{
		lTree->balance = -1;
		tmp->left->balance = 0;
		tmp->balance = 0;
	}
	
	return tmp; 
}

/* 
 * Parameters:
 * binTreeNode_t **root_tree : The root node of current child tree
 * binTreeNode_t *pNewNode:	The node waited to be inserted
 *
 * Return value: 0	balance not change
 * 				 1	balance add 1
 *				-1	balance decrease 1
 */
int insert_into_tree(binTreeNode_t **root_tree, binTreeNode_t *pNewNode)
{	
	if(pNewNode->key < (*root_tree)->key)
	{
		if(!(*root_tree)->left)	/* The left child is NULL, insert into left child */
		{
			(*root_tree)->left = pNewNode;
			pNewNode->balance = 0;
			(*root_tree)->balance++;	/* Calculate new balance for current node */
			if((*root_tree)->balance == 1)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			/* Going to left tree */
			/* Calculate new balance for the current node */
			int balance_change = insert_into_tree(&((*root_tree)->left), pNewNode);
			if(balance_change == 3)
			{
				return balance_change;	/* Existed node, return 3 */
			}
			(*root_tree)->balance += balance_change;	/* Insert into left child tree, balance add 1 */
			switch((*root_tree)->balance)
			{
				case -1:
					return 0;
				case 0:
					return 0;
				case 1:
					return balance_change;
				case 2:
					if((*root_tree)->left->balance == 1)
					{
						*root_tree = rotate_LL(*root_tree);
					}
					else if((*root_tree)->left->balance == -1)
					{
						*root_tree = rotate_LR(*root_tree);
					}
					return 0;	/* Rotation will not change balance, return 0 */
				default:
					fprintf(stderr, "Invalid Balance, id: %d, balance: %d\n", (*root_tree)->key, (*root_tree)->balance);
					exit(EXIT_FAILURE);
			}
		}
	} 
	else if(pNewNode->key > (*root_tree)->key)
	{
		/* Going to right tree */
		if(!(*root_tree)->right)
		{
			(*root_tree)->right = pNewNode;
			pNewNode->balance = 0;
			(*root_tree)->balance--;
			if((*root_tree)->balance == -1)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			/* Going to right tree */
			int balance_change = insert_into_tree(&((*root_tree)->right), pNewNode);
			if(balance_change == 3)
			{
				return balance_change;	/* Existed node, return 3 */
			}

			(*root_tree)->balance -= balance_change;	/* Insert into right child tree, balance decrease 1 */
			switch((*root_tree)->balance)
			{
				case 0:
					return 0;
				case 1:
					return 0;
				case -1:
					return balance_change;
				case -2:
					if((*root_tree)->right->balance == -1)
					{
						*root_tree = rotate_RR(*root_tree);
					}
					else if((*root_tree)->right->balance == 1)
					{
						*root_tree = rotate_RL(*root_tree);
					}
					return 0;	/* Rotation will not change balance, return 0 */
				default:
					fprintf(stderr, "Invalid Balance, id: %d, balance: %d\n", (*root_tree)->key, (*root_tree)->balance);
					exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		return 3;	/* Existed node, return 3 */
	}
	return -1;
}

/*
 * Insert a value.
 * NOTE: For this assignment, we don't want duplicates.
 */
int insertTreeNode(BinTree_t *pTree, binTreeNode_t *pNewNode)
{
	int ret = FAILED;
	/* TODO: Implement me! */
	/* Note you are free to change the interface or add another function to add tree nodes.  But you will need to update deleteKey(). */
	if(!pTree->root)
	{
		/* The tree is NULL, create first node for the tree */
		pTree->root = pNewNode;
		pNewNode->balance = 0;
	}
	else
	{
		if(pNewNode->key == pTree->root->key)
		{
			/* Existed vertex */
			return EXISTING_VERTEX;
		}
		else
		{
			ret = insert_into_tree(&(pTree->root), pNewNode);
			if(ret == 3)
			{
				return EXISTING_VERTEX;
			}
			else if(ret == -1)
			{
				return FAILED;
			}
		}
	}
	return SUCCESS;
} /* end of insertValue() */

void free_node(binTreeNode_t* node)
{
	freeValueMemory(node->value);
	safeFree(node, sizeof(binTreeNode_t));
}

/* Find the largest node of left tree and swap it with root node 
 * paremeter:
 *	root	delete node
 *	parent	parent of largest node
 *  parent_right	largest node of left tree
*/
int swap_and_delete_left(binTreeNode_t **root, binTreeNode_t *parent, binTreeNode_t *parent_right)
{
	if(!parent_right->right)
	{
		if(parent == parent_right)
		{
			/* The first left child of deletion node is the largest left side child */
			int root_balance = (*root)->balance;
			parent->right = (*root)->right;
			free_node(*root);
			*root = parent;
			(*root)->balance = root_balance - 1;
			return 1;
		}
		else
		{
			/* swap the largest node and the delete node, delete the node */
			binTreeNode_t *tmp = parent_right->left;
			binTreeNode_t *delete_node = *root;
			parent_right->left = (*root)->left;
			parent_right->right = (*root)->right;
			*root = parent->right;
			parent->right = tmp;
			
			free_node(delete_node);
			delete_node = NULL;
			
			parent->balance++;
			
			switch(parent->balance)
			{
				case 0:
					return 1;
				case 1:
					return 0;
				case 2:
					parent = rotate_LL(parent);
					return 1;
				default:
					fprintf(stderr, "Invalid balance\n");
					exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		parent->balance += swap_and_delete_left(root, parent->right, parent->right->right);
		switch(parent->balance)
		{
			case 0:
				return 1;
			case 1:
				return 0;
			case 2:
				if(parent->left->balance >= 0)
				{
					/* Make a LL rotate */
					parent = rotate_LL(parent);
					return 1;
				}
				else
				{
					/* Make a LR rotate */
					parent = rotate_LR(parent);
					return 1;
				}
			default: fprintf(stderr, "Invalid balance\n");
					 exit(EXIT_FAILURE);
		}
	}
}


/* Find the smallest node of right tree and swap it with root node 
 * paremeter:
 *	root	delete node
 *	parent	parent of smallest node
 *  parent_left	smallest node of right tree
*/
int swap_and_delete_right(binTreeNode_t **root, binTreeNode_t *parent, binTreeNode_t *parent_left)
{
	if(!parent_left->left)
	{
		if(parent == parent_left)
		{
			/* The first right child of deletion node is the smallest right side child */
			int root_balance = (*root)->balance;
			parent->left = (*root)->left;
			free_node(*root);
			*root = parent;
			(*root)->balance = root_balance + 1;
			return 1;
		}
		else
		{
			/* swap the smallest node and the left child of delete node, delete the node */
			binTreeNode_t *tmp = parent_left->right;
			binTreeNode_t *delete_node = *root;
			parent_left->right = (*root)->right;
			parent_left->left = (*root)->left;
			*root = parent->left;
			parent->left = tmp;
			
			free_node(delete_node);
			delete_node = NULL;
			
			parent->balance--;
			
			switch(parent->balance)
			{
				case 0:
					return 1;
				case -1:
					return 0;
				case -2:
					parent = rotate_RR(parent);
					return 1;
				default:
					fprintf(stderr, "Invalid balance\n");
					exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		parent->balance -= swap_and_delete_right(root, parent->left, parent->left->left);
		switch(parent->balance)
		{
			case 0:
				return 1;
			case -1:
				return 1;
			case -2:
				if(parent->right->balance <= 0)
				{
					/* Make a RR rotate */
					parent = rotate_RR(parent);
					return 1;
				}
				else
				{
					/* Make a LR rotate */
					parent = rotate_RL(parent);
					return 1;
				}
			default: fprintf(stderr, "Invalid balance\n");
					 exit(EXIT_FAILURE);
		}
	}
}

int delete_key(binTreeNode_t **root)
{
	if(!((*root)->left) && !((*root)->right))
	{
		/* Node has no children */
		free_node(*root);
		(*root) = NULL;
		return 1;
	}
	else if((*root)->left && (*root)->right)
	{
		/* Node has two children */
		if((*root)->balance >= 0)
		{
			int ret = swap_and_delete_left(root, (*root)->left, (*root)->left);
			return ret;
		}
		else
		{
			int ret = swap_and_delete_right(root, (*root)->right, (*root)->right);
			return ret;
		}
	}
	else if((*root)->left)
	{
		/* Node has left child */
		binTreeNode_t *tmp = *root;
		*root = (*root)->left;
		free_node(tmp);
		return 1;
	}
	else
	{
		/* Node has right child */
		binTreeNode_t *tmp = *root;
		*root = (*root)->right;
		free_node(tmp);
		return 1;
	}
	return -1;
}


int delete_vertex(binTreeNode_t **root, int key)
{
	if(!root)
	{
		fprintf(stderr, "Error: delete tree is null\n");
		exit(EXIT_FAILURE);
	}
	if(*root == NULL)
	{
		return FAILED;
	}
	
	if(key == (*root)->key)
	{
		return delete_key(root);
	}
	else if(key < (*root)->key)
	{
		/* Traverse left tree */
		int ret = delete_vertex(&((*root)->left), key);
		(*root)->balance -= ret;
		switch((*root)->balance)
		{
			case 0:
				return ret;
			case -1:
				return ret;
			case -2:
				if((*root)->right->balance <= 0)
				{
					*root = rotate_RR(*root);
					return 1;
				}
				else
				{
					*root = rotate_RL(*root);
					return 1;
				}
		}
	}
	else
	{
		/* Traverse right tree */
		int ret = delete_vertex(&((*root)->right), key);
		(*root)->balance += ret;
		switch((*root)->balance)
		{
			case 0:
				return ret;
			case 1:
				return ret;
			case 2:
				if((*root)->left->balance >= 0)
				{
					*root = rotate_LL(*root);
					return 1;
				}
				else
				{
					*root = rotate_LR(*root);
					return 1;
				}
		}
	}
	return FAILED;
}


/* ******************************************************************** */


binTreeNode_t* searchNode(binTreeNode_t *pTree, int key)
{
	binTreeNode_t *pCurrNode = pTree;
	
	while (pCurrNode != NULL) {
		if (key == pCurrNode->key)
		{
			break;
		}
		else if (key < pCurrNode->key) 
		{
			/* Smaller than current node, search left child tree */
			pCurrNode = searchNode(pCurrNode->left, key);
		}
		else 
		{
			/* Bigger than current node, search right child tree */
			pCurrNode = searchNode(pCurrNode->right, key);
		}
	}
	
	return pCurrNode;
} 

/* Return the parent node of delete node 
 * if the root is the key then return NULL
 * or if cannot find the key return NULL 
*/
binTreeNode_t *search_delete_node(binTreeNode_t *pTree, int key)
{
	binTreeNode_t *parent_node = NULL;
	binTreeNode_t *pCurrNode = pTree;
	
	while (1) {
		if(key == pTree->key)
		{
			break;
		}
		else if (key < pCurrNode->key) 
		{
			/* Smaller than current node, search left child tree */
			if(!pCurrNode->left)
			{
				/* Cannot find node */
				return NULL;
			}
			else
			{
				parent_node = pCurrNode;
				if(key == pCurrNode->left->key)
				{
					break;
				}
				else
				{
					pCurrNode = pCurrNode->left;
				}	
			}
		}
		else 
		{
			/* Bigger than current node, search right child tree */
			if(!pCurrNode->right)
			{
				/* Cannot find node */
				return NULL;
			}
			else
			{
				parent_node = pCurrNode;
				if(key == pCurrNode->right->key)
				{
					break;
				}
				else
				{
					pCurrNode = pCurrNode->right;
				}	
			}
		}
	}
	return parent_node;
} /* end of searchDeleteNode() */



/* ******************************************************************** */


void print_tree_test(binTreeNode_t *pTree)
{
	binTreeNode_t *current = pTree;
	while(current)
	{
		printf("%d balance-> %d\n", current->key, current->balance);
		if(current->left)
		{
			printf("lc: %d\n", current->left->key);
		}
		if(current->right)
		{
			printf("rc: %d\n", current->right->key);
		}
		print_tree_test(current->left);
		print_tree_test(current->right);
		return;
	}
}


void free_edge_list(Edge_t* head)
{
	if(!head)
	{
		return;
	}
	Edge_t *current = head->next;
	safeFree(head, sizeof(Edge_t));
	while(current)
	{
		Edge_t *tmp = current;
		current = current->next;
		safeFree(tmp, sizeof(Edge_t));
	}
	return;
}

/* TODO: Please implement and move these functions to most appropriate file. */
void freeValueMemory(void *value)
{
	/* TODO: Implement me! */
	free_edge_list(value);
	return;
}


