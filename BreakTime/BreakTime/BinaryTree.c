#pragma once
#include "BinaryTree.h"
#include <stdlib.h>


//this exists so we can "know" as much as you can know in C who owns the allocated space in the tree
//which means we can avoid memory leaks and access violations, by treating the whole thing as one allocated "unit"
BinaryTree* new_tree(void* payload, size_t payload_size)
{
	BinaryTree* result = malloc(sizeof(BinaryTree));
	if (result != 0)
	{
		result->left = 0;
		result->right = 0;
		result->content = malloc(payload_size);
		if (result->content != 0)
		{
			memcpy(result->content, payload, payload_size);
		}
	}
	//for the time being we're likely to just eat not allocating the memory, it's recoverable in that it won't cause a crash
	// but it also doesn't what we want it to
	//TODO: make this a fail state for the entire application.  No idea how to test this case.  
	//      Intentionally malloc the whole computer's ram prior to execution?
	return result;
}

/// <summary>
/// Inserts an item into a tree if not already present
/// </summary>
/// <param name="tree">the binary tree to insert into</param>
/// <param name="payload">arbitrary payload content</param>
/// <param name="payload_size">the size of the payload type in memory</param>
/// <param name="cmpPointer">a pointer to comparison function that compares an item to the payload type</param>
/// <returns></returns>
int tree_insert(BinaryTree* tree, void* payload, size_t payload_size, int (*cmpPointer)(void*, void*))
{
	if (tree == 0)
	{
		//how did we even get to this state?
		exit(1);
	}
	int comparison = cmpPointer(payload, tree->content);
	//if we have an exact match, we do not insert anything
	if (comparison == 0)
		return 0;
	else if (comparison < 0)
	{
		if (tree->left == 0)
		{
			tree->left = new_tree(payload, payload_size);
			return 1;
		}
		else
		{
			return tree_insert(tree->left, payload, payload_size, cmpPointer);
		}
	}
	//could be am implicit else, but I like to be explicit for readability
	else if (comparison > 0)
	{
		if (tree->right == 0)
		{
			tree->right = new_tree(payload, payload_size);
			return 1;
		}
		else
		{
			return tree_insert(tree->right, payload, payload_size, cmpPointer);
		}
	}
}

/// <summary>
/// Frees the tree AND its content
/// </summary>
/// <param name="tree"></param>
void free_tree(BinaryTree* tree)
{
	if (tree == 0)
		return;
	if (tree->left != 0)
	{
		free_tree(tree->left);
	}
	if (tree->right != 0)
	{
		free_tree(tree->right);
	}
	if (tree->content != 0)
	{
		free(tree->content);
	}
	free(tree);
}