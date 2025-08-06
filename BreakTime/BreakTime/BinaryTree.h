#pragma once
#include <string.h>

typedef struct BinaryTree BinaryTree;

struct BinaryTree
{
	BinaryTree* left;
	BinaryTree* right;
	void* content;
};

BinaryTree* new_tree(void* payload, size_t payload_size);

int tree_insert(BinaryTree* tree, void * payload, size_t payload_size, int (*cmpPointer)(void*, void*));

void free_tree(BinaryTree* tree);