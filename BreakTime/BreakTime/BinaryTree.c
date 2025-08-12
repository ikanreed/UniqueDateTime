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
		result->count = 1;
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
/// Takes a binary tree and produces a copy of it, with balanced structure(slight left bias).  
/// Procedure: 
/// 1.  creates an array with capacity equal to the tree
/// 2.  fills array with sorted values from the tree
/// 3.  takes the midpoints of the array and adds them to a new 
/// </summary>
/// <param name="toBalance">The tree to produce a </param>
/// <param name="payload_size">The size in memory of one value in the tree</param>
/// <param name="cmpPointer">A comparison function for values of the tree's type</param>
/// <returns>A new balanced tree with new copies of the content, please remember to free the old tree if done</returns>
BinaryTree* balance_binary_tree(BinaryTree* toBalance, size_t payload_size, ComparisonFunction* cmpPointer)
{
	//base case, don't make copies of null
	if (toBalance == 0)
		return 0;
	if (toBalance->count == 0)
	{
		//TODO: this is a broken binary tree object, send caller a null back for now.
		return 0;
	}
	void** buffer = (void**)malloc(sizeof(void*) * toBalance->count);
	if (buffer == 0)
	{
		//if we can't allocate a new buffer, return null pointer. 
		return 0;
	}
	add_tree_content_to_array(toBalance, buffer, 0);

	int center = toBalance->count / 2;
	//kind of less than maximally elegant here.  Because we don't support empty trees, create the node to add everything to first, then add the left, then the right
	BinaryTree* result = new_tree(buffer[center],payload_size);
	
	add_array_content_to_tree(buffer, result, 0, center, payload_size, cmpPointer);
	add_array_content_to_tree(buffer, result, center + 1, toBalance->count - (center + 1), payload_size, cmpPointer);
	//when we're done with balancing the tree, clean up the temporary buffer used to balance it
	free(buffer);

	return result;
}

/// <summary>
/// Fills an array with items from the tree(sorted)
/// </summary>
/// <param name="treeNode">A binary tree node to pack</param>
/// <param name="buffer">The array to fill with tree elements</param>
/// <param name="startIndex">The starting place in the buffer to write to</param>
void add_tree_content_to_array(BinaryTree* treeNode, void** buffer, int startIndex)
{
	if (treeNode == 0)
		return;
	int center = startIndex+0;
	if (treeNode->left != 0)
	{
		center = startIndex+treeNode->left->count;
	}
	buffer[center] = treeNode->content;
	add_tree_content_to_array(treeNode->left, buffer, 0);
	add_tree_content_to_array(treeNode->right, buffer, center + 1);
}

/// <summary>
/// Adds sorted array to tree, in a balanced way to remain performative, primarily intended to be used internally,
/// but it could be used when known pre-sorted data is added en masse
/// </summary>
/// <param name="buffer">An array containing pointers to tree payloads</param>
/// <param name="treeNode">The ROOT of the tree to add to.</param>
/// <param name="startIndex">The starting index of buffer to read from, usually zero</param>
/// <param name="count">The number of items to read from the buffer</param>
/// <param name="payload_size">The size of each item in memory</param>
/// <param name="cmpPointer">A function that compares two tree payload items</param>
void add_array_content_to_tree(void** buffer, BinaryTree* treeNode, int startIndex, int count, size_t payload_size, ComparisonFunction* cmpPointer)
{
	if (count == 0)
		return;
	int midpoint = startIndex + count / 2;
	tree_insert(treeNode, buffer[midpoint], payload_size, cmpPointer);
	//e.g.  slots are buffer[0..2] count is 3 midpoint is 1, so what's to the left is [0..0] or a count of 1
	//edge case of 1 item, should leave us with the base case of zero items on the left that recursive call returns after doing nothing 
	int leftCount = midpoint - startIndex;
	//and we have to fill _count_ total items, 1 is our new midpoint of our tree, leftCount is what's to the left, so the right is count minus those
	int rightCount = count - leftCount - 1;
	add_array_content_to_tree(buffer, treeNode, startIndex, leftCount, payload_size, cmpPointer);
	add_array_content_to_tree(buffer, treeNode, midpoint + 1, rightCount, payload_size, cmpPointer);

}

/// <summary>
/// Inserts an item into a tree if not already present
/// </summary>
/// <param name="tree">the binary tree to insert into</param>
/// <param name="payload">arbitrary payload content</param>
/// <param name="payload_size">the size of the payload type in memory</param>
/// <param name="cmpPointer">a pointer to comparison function that compares an item to the payload type</param>
/// <returns>Number of items added to tree(i.e. 0 if already present)</returns>
int tree_insert(BinaryTree* tree, void* payload, size_t payload_size,ComparisonFunction* cmpPointer)
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
			tree->count++;
			return 1;
		}
		else
		{
			int addedItemCount= tree_insert(tree->left, payload, payload_size, cmpPointer);
			tree->count += addedItemCount;
			return addedItemCount;
		}
	}
	//could be am implicit else, but I like to be explicit for readability
	else if (comparison > 0)
	{
		if (tree->right == 0)
		{
			tree->right = new_tree(payload, payload_size);
			tree->count++;
			return 1;
		}
		else
		{
			int addedItemCount= tree_insert(tree->right, payload, payload_size, cmpPointer);
			tree->count += addedItemCount;
			return addedItemCount;
		}
	}
}

/// <summary>
/// Frees the tree AND its content, which is copied when the tree is produced or inserted into.
/// </summary>
/// <param name="tree">The tree whose memory allocations are to be freed</param>
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