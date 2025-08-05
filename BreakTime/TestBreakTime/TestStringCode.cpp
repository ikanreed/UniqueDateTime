#include "pch.h"
#include "CppUnitTest.h"
extern "C" {
#include "StringHelper.h"
}


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestBreakTime
{
	TEST_CLASS(TestStringCode)
	{
	public:

		TEST_METHOD(TestTrim)
		{
			//none of our test cases are longer than that
			char resultString[100];
			int resultLength;
			trimstring("     ", 5, resultString);
			Assert::AreEqual("", resultString);

			trimstring(" asdf    ", 9, resultString);
			Assert::AreEqual("asdf", resultString);


			trimstring("sdf    ", 7, resultString);
			Assert::AreEqual("sdf", resultString);


			trimstring("\r\n\tf", 4, resultString);
			Assert::AreEqual("f", resultString);


			trimstring("", 0, resultString);
			Assert::AreEqual("", resultString);

			//buffer underflow should be fine
			trimstring("lots of text", 0, resultString);
			Assert::AreEqual("", resultString);

			//buffer overflow should be fine
			trimstring("", 20, resultString);
			Assert::AreEqual("", resultString);

		}
	};
}