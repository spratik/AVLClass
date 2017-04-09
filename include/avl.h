/*
 * header.h
 *
 *  Created on: Jul 25, 2016
 *      Author: root
 */

#ifndef HEADER_H_
#define HEADER_H_


#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <list>
#include <map>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <algorithm>
#include <set>
using namespace std;

// An AVL tree node

class AVL
{
public:

	struct node
	{
		char* key = NULL;
		struct node *left;
		struct node *right;
		int height;
	};

	node *root;
	node *temp;

	// A utility function to get height of the tree
	int height(struct node *N)
	{
		if (N == NULL)
			return 0;
		return N->height;
	}

	// A utility function to get maximum of two integers
	int max(int a, int b)
	{
		return (a > b)? a : b;
	}

	//Helper function that allocates a new node with the given key and
	//NULL left and right pointers.
	struct node* newNode(const char* key)
	{
		struct node* node = (struct node*)malloc(sizeof(struct node));

		node->key = (char *)calloc(strlen(key) + 1, sizeof(char));

		strcpy(node->key , key);

		node->left = NULL;
		node->right = NULL;
		node->height = 1; // new node is initially added at leaf
		return(node);
	}

	// A utility function to right rotate subtree rooted with y
	// See the diagram given above.
	struct node *rightRotate(struct node *y)
	{
		struct node *x = y->left;
		struct node *T2 = x->right;

		// Perform rotation
		x->right = y;
		y->left = T2;

		// Update heights
		y->height = max(height(y->left), height(y->right))+1;
		x->height = max(height(x->left), height(x->right))+1;

		// Return new root
		return x;
	}

	// A utility function to left rotate subtree rooted with x
	// See the diagram given above.
	struct node *leftRotate(struct node *x)
	{
		struct node *y = x->right;
		struct node *T2 = y->left;

		// Perform rotation
		y->left = x;
		x->right = T2;

		// Update heights
		x->height = max(height(x->left), height(x->right)) + 1;
		y->height = max(height(y->left), height(y->right)) + 1;

		// Return new root
		return y;
	}

	// Get Balance factor of node N
	int getBalance(struct node *N)
	{
		if (N == NULL)
			return 0;
		return height(N->left) - height(N->right);
	}

	struct node* insert(struct node* node, const char* key)
	{
		// 1. Perform the normal BST rotation
		if (node == NULL)
			return(newNode(key));

		if (strcmp(key, node->key) < 0){
			node->left = insert(node->left, key);
		} else{
			node->right = insert(node->right, key);
		}

		//2. Update height of this ancestor node
		node->height = max(height(node->left), height(node->right)) + 1;


		//3. Get the balance factor of this ancestor node to check whether
		//this node became unbalanced
		int balance = getBalance(node);

		// If this node becomes unbalanced, then there are 4 cases

		// Left Left Case
		if (balance > 1 && strcmp(key, node->left->key) < 0)
			return rightRotate(node);

		// Right Right Case
		if (balance < -1 && strcmp(key, node->right->key) > 0)
			return leftRotate(node);

		// Left Right Case
		if (balance > 1 && strcmp(key, node->left->key) > 0)
		{
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}

		// Right Left Case
		if (balance < -1 && strcmp(key, node->right->key) < 0)
		{
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}

		//return the (unchanged) node pointer
		return node;
	}

	// A utility function to print preorder traversal of the tree.
	// The function also prints height of every node
	void preOrder(struct node *root)
	{
		if(root != NULL)
		{
			printf("%s ", root->key);
			printf("height = %d \n", root-> height);
			fflush(stdout);
			preOrder(root->left);
			preOrder(root->right);
		}
	}

	vector <string> getBuffer(ifstream &myfile){
		vector <string > htableBuffer;

		string line;

		//cout << myfile.is_open() << endl;

		if (myfile.is_open())
		{
			while (getline (myfile,line))
			{
				htableBuffer.push_back(line);
			}
			myfile.close();
		}else
		{
			cout << "unable to open the file" << endl;
		}

		return htableBuffer;
	}
	struct node* search(struct node *root, const char* val)
	{
		if(!root)
		{
			return NULL;
		}

		int flag = strcmp(val, root->key);

		if(flag < 0)
		{
			search(root->left, val);
		}
		else if(flag > 0)
		{
			search(root->right, val);
		}
		else if(flag == 0)
		{
			return root;
		}
	}
	/* Given a non-empty binary search tree, return the node with minimum
	   key value found in that tree. Note that the entire tree does not
	   need to be searched. */
	struct node * minValueNode(struct node* node)
	{
	    struct node* current = node;

	    /* loop down to find the leftmost leaf */
	    while (current->left != NULL)
	        current = current->left;

	    return current;
	}

	struct node* deleteNode(struct node* root, char *key)
	{
	    // STEP 1: PERFORM STANDARD BST DELETE

	    if (root == NULL)
	        return root;

	    // If the key to be deleted is smaller than the root's key,
	    // then it lies in left subtree
	    if ( strcmp(key , root->key) < 0)
	        root->left = deleteNode(root->left, key);

	    // If the key to be deleted is greater than the root's key,
	    // then it lies in right subtree
	    else if( strcmp (key , root->key) > 0)
	        root->right = deleteNode(root->right, key);

	    // if key is same as root's key, then This is the node
	    // to be deleted
	    else
	    {
	        // node with only one child or no child
	        if( (root->left == NULL) || (root->right == NULL) )
	        {
	            struct node *temp = root->left ? root->left : root->right;

	            // No child case
	            if(temp == NULL)
	            {
	                temp = root;
	                root = NULL;
	            }
	            else // One child case
	             *root = *temp; // Copy the contents of the non-empty child

	            free(temp);
	        }
	        else
	        {
	            // node with two children: Get the inorder successor (smallest
	            // in the right subtree)
	            struct node* temp = minValueNode(root->right);

	            // Copy the inorder successor's data to this node
	            root->key = temp->key;

	            // Delete the inorder successor
	            root->right = deleteNode(root->right, temp->key);
	        }
	    }

	    // If the tree had only one node then return
	    if (root == NULL)
	      return root;

	    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
	    root->height = max(height(root->left), height(root->right)) + 1;

	    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether
	    //  this node became unbalanced)
	    int balance = getBalance(root);

	    // If this node becomes unbalanced, then there are 4 cases

	    // Left Left Case
	    if (balance > 1 && getBalance(root->left) >= 0)
	        return rightRotate(root);

	    // Left Right Case
	    if (balance > 1 && getBalance(root->left) < 0)
	    {
	        root->left =  leftRotate(root->left);
	        return rightRotate(root);
	    }

	    // Right Right Case
	    if (balance < -1 && getBalance(root->right) <= 0)
	        return leftRotate(root);

	    // Right Left Case
	    if (balance < -1 && getBalance(root->right) > 0)
	    {
	        root->right = rightRotate(root->right);
	        return leftRotate(root);
	    }

	    return root;
	}
};





#endif /* HEADER_H_ */
