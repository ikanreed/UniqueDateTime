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
	};
}