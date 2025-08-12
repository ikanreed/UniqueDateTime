#include "pch.h"
#include "CppUnitTest.h"
extern "C" {
#include "BinaryTree.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestBreakTime
{
	int IntComparison(void* va, void* vb)
	{
		int* a = (int*)va;
		int* b = (int*)vb;
		if (a == 0 && b == 0)
			return 0;
		if (a == 0)
			return 1;
		if (b == 0)
			return 1;
		return *a - *b;
	}

	TEST_CLASS(TestBinaryTree)
	{
	public:

		TEST_METHOD(TestInsert)
		{
			int base = 15;
			int leftval = 10;
			int midval = 13;
			BinaryTree* tree = new_tree((void*) & base, sizeof(int));
			void* content = tree->content;
			int* asint = (int*)content;
			int val = *asint;
			Assert::AreEqual(15, *((int*)tree->content));

			int result = tree_insert(tree, &leftval, sizeof(int), &IntComparison);
			Assert::AreEqual(result, 1);
			Assert::AreEqual(10, *((int*)tree->left->content));

			result = tree_insert(tree, &leftval, sizeof(int), &IntComparison);
			//we expect to return 0 for whether we added the value
			Assert::AreEqual(result, 0);
			Assert::AreEqual(10, *((int*)tree->left->content));


			result = tree_insert(tree, &midval, sizeof(int), &IntComparison);
			Assert::AreEqual(result, 1);
			Assert::AreEqual(13, *((int*)tree->left->right->content));

			//I don't know if we have any expectations that this does anything
			free_tree(tree);
		}

		TEST_METHOD(TestBalance)
		{
			//we choose 7 for this case because it results in a perfectly balanced tree afterwards, easy to test

			int sortedInts[7] = { 0,1,2,3,4,5,6 };
			//technically we could just (void*)sortedInts, but it feels wrong to me
			BinaryTree* intTree = new_tree((void*)&(sortedInts[0]), sizeof(int));
			//produce a very badly balanced tree by adding sorted items in order
			for (int i = 1; i < 7; i++)
			{
				int added = tree_insert(intTree, (void*)&(sortedInts[i]), sizeof(int), &IntComparison);
				//we expect to be able to add 9 more (unique) ints without issue
				Assert::AreEqual(1, added);
			}
			//we expect the operation to result in a tree with 7 items
			Assert::AreEqual(7, intTree->count);

			//we expect the tree to be totally unbalanced and the fourth item going right to the same as the fourth item from our array
			Assert::AreEqual(3, *((int*)intTree->right->right->right->content));

			BinaryTree* balancedTree = balance_binary_tree(intTree, sizeof(int), &IntComparison);
			// should be
			//     3
			//   1    5
			// 0   2 4  6
			Assert::AreEqual(3, *(int*)balancedTree->content);
			Assert::AreEqual(2, *(int*)balancedTree->left->right->content);
			Assert::AreEqual(6, *(int*)balancedTree->right->right->content);
		}
	};
}