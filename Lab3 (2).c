/*******************************************************************************************
 * File Name	: Lab3.c

 * Description	: This file is the skeleton for lab 3 (Binary Search Tree)
 *
 * Instructions	: 
			- Complete binarySearchTree_AddNode() and binarySearchTree_PrintTreeInOrder() functions.
 *
 * Student Name:
 * Student Number:
 */
#include <stdio.h>
#include <stdlib.h>


typedef struct
{
	char key[10];	// A string representing a key
	int iData;
} data_t;

// Structure defining a binary tree node.  Lower sorted values will go the the left, higher to the pRight.
typedef struct node
{
	data_t data;		// Contains data and a key
	struct node* pLeft;
	struct node *pRight;
}node_t;


// Data to be stored in tree.
data_t inputData[] =
{
	{{ "blue"}, 85},
	{{ "red"}, 77},
	{{ "yellow"}, -4},
	{{ "white"}, 152},
	{{ "black"}, 0},
	{{ "green"}, -33},
	{{ "orange"}, 275},
	{{ "purple"}, 654},
	{{ "brown"}, 99},
	{{ "grey"}, -5}
	
};


void binarySearchTree_AddNode(node_t **ppRoot, data_t *pData);
void binarySearchTree_PrintTreeInOrder(node_t *pRoot);
void binarySearchTree_deleteTree(node_t** ppNode);


/**
* Brief: This function adds a new node to the binary search tree
* Inputs:
*       ppRoot - Pointer to the root's reference
*       pData - Pointer to data to be added
*/
void binarySearchTree_AddNode(node_t** ppRoot, data_t* pData)
{
	// Add code to put items into binary tree in alphabetical order here
	// Hint: Consider using strcmp library function to decide if a name is greater or less than
	node_t* temp = (node_t*)malloc(sizeof(node_t));
	temp->data = *pData;
	temp->pLeft = NULL;
	temp->pRight = NULL;

	if (*ppRoot == NULL)
	{
		*ppRoot = temp;
		 return;
	}
	struct  node* x = *ppRoot;
	if (pData->iData < x->data.iData)
		{
			binarySearchTree_AddNode(&((*ppRoot)->pLeft), pData);
		}
	else
		{
			binarySearchTree_AddNode(&((*ppRoot)->pRight), pData);
		}
		
}

/**
* Brief: This function prints all the contents of the binary search tree in the ascending order (smaller to greater).
* Inputs:
*       pRoot - Pointer to the root
*/
void binarySearchTree_PrintTreeInOrder(node_t* pRoot)
{
	if (pRoot != NULL)
	{
		binarySearchTree_PrintTreeInOrder(pRoot->pLeft);
		printf("%s: %d\n", pRoot->data.key, pRoot->data.iData);
		binarySearchTree_PrintTreeInOrder(pRoot->pRight);
	}
	
}


/**
* Brief: This function deletes all the nodes in the binary search tree
* Inputs:
*       ppRoot - Pointer to the root's reference
*/
void binarySearchTree_deleteTree(node_t** ppNode)
{
	if (*ppNode != NULL)
	{
		binarySearchTree_deleteTree(&(*ppNode)->pLeft);
		binarySearchTree_deleteTree(&(*ppNode)->pRight);
		free(*ppNode);
		*ppNode = NULL;
	}
}


int main()
{
	node_t* pRoot = NULL;	// Pointer to root of the binary tree

	// Insert all the data into the binary tree
	int i;
	for (i = 0; i < (sizeof(inputData) / sizeof(inputData[0])); i++)
	{
		binarySearchTree_AddNode(&pRoot, &inputData[i]);
	}

	// Print the entire tree.  It should come out in alphabetical order.
	binarySearchTree_PrintTreeInOrder(pRoot);

	binarySearchTree_deleteTree(&pRoot);

	// Make sure deletion was successful
	binarySearchTree_PrintTreeInOrder(pRoot);

	return 0;
}
