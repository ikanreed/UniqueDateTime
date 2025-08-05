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
			char* resultString;
			int resultLength;
			trimstring("     ", 5, &resultString, &resultLength);
			Assert::AreEqual("", resultString);
			free(resultString);

			trimstring(" asdf    ", 9, &resultString, &resultLength);
			Assert::AreEqual("asdf", resultString);
			free(resultString);


			trimstring("sdf    ", 7, &resultString, &resultLength);
			Assert::AreEqual("sdf", resultString);
			free(resultString);


			trimstring("\r\n\tf", 4, &resultString, &resultLength);
			Assert::AreEqual("f", resultString);
			free(resultString);


			trimstring("", 0, &resultString, &resultLength);
			Assert::AreEqual("", resultString);
			free(resultString);

			//buffer underflow should be fine
			trimstring("lots of text", 0, &resultString, &resultLength);
			Assert::AreEqual("", resultString);
			free(resultString);

			//buffer overflow should be fine
			trimstring("", 20, &resultString, &resultLength);
			Assert::AreEqual("", resultString);
			free(resultString);

		}
	};
}