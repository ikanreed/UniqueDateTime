#include "pch.h"
#include "CppUnitTest.h"
extern "C" {
#include "DateTimeStruct.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestBreakTime
{
	TEST_CLASS(TestBreakTime)
	{
	public:
		
		TEST_METHOD(TestValidateDatetimeString)
		{
			char* ObviouslyGood = "2025-08-04T10:52:00-05:00";
			int goodResult = validate_datetime_string_format(ObviouslyGood, sizeof(ObviouslyGood));
			Assert::AreEqual(0, goodResult);
		}
	};
}
