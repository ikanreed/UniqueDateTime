#pragma once
#include <string.h>

typedef struct BinaryTree BinaryTree;

typedef int ComparisonFunction(void*, void*);

struct BinaryTree
{
	int count;
	BinaryTree* left;
	BinaryTree* right;
	void* content;
};

BinaryTree* new_tree(void* payload, size_t payload_size);

BinaryTree* balance_binary_tree(BinaryTree* toBalance, size_t payload_size, ComparisonFunction* cmpPointer);
void add_tree_content_to_array(BinaryTree* tree, void** buffer, int startIndex);
void add_array_content_to_tree(void** buffer, BinaryTree* root, int startIndex, int count, size_t payload_size, ComparisonFunction* cmpPointer);

int tree_insert(BinaryTree* tree, void * payload, size_t payload_size, ComparisonFunction* cmpPointer);

void free_tree(BinaryTree* tree);