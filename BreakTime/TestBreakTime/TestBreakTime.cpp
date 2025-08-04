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
			int goodResult = validate_datetime_string_format(ObviouslyGood, strlen(ObviouslyGood));
			Assert::AreEqual(0, goodResult);
			
			char* UTCTz = "2025-08-04T10:52:00Z";
			int UTCresult = validate_datetime_string_format(UTCTz, strlen(UTCTz));
			Assert::AreEqual(0, UTCresult);


			char* yearNotNumeric = "20A5-08-04T10:52:00-05:00";
			int yearNotNumericResult = validate_datetime_string_format(yearNotNumeric, strlen(yearNotNumeric));
			//for now all our invalid string error codes are 1
			Assert::AreEqual(1, yearNotNumericResult);

			char* monthNotNumeric = "2025-{8-04T10:52:00-05:00";
			int monthNotNumericResult = validate_datetime_string_format(monthNotNumeric, strlen(monthNotNumeric));
			//for now all our invalid string error codes are 1
			Assert::AreEqual(1, monthNotNumericResult);

			char* dayNotNumeric = "2025-08-0*T10:52:00-05:00";
			int dayResult = validate_datetime_string_format(dayNotNumeric, strlen(dayNotNumeric));
			//for now all our invalid string error codes are 1
			Assert::AreEqual(1, dayResult);

			char* hourNotNumeric = "2025-08-04T1P:52:00-05:00";
			int hourResult = validate_datetime_string_format(hourNotNumeric, strlen(hourNotNumeric));
			Assert::AreEqual(1, hourResult);

			char* minuteNotNumeric = "2025-08-04T10:5X:00-05:00";
			int minuteResult = validate_datetime_string_format(minuteNotNumeric, strlen(minuteNotNumeric));
			Assert::AreEqual(1, minuteResult);

			char* secondNotNumeric = "2025-08-04T10:52:0I-05:00";
			int secondResult = validate_datetime_string_format(secondNotNumeric, strlen(secondNotNumeric));
			Assert::AreEqual(1, secondResult);

			char* TZHourNotNumeric = "2025-08-04T10:52:00-O5:00";
			int tzHourResult = validate_datetime_string_format(TZHourNotNumeric, strlen(TZHourNotNumeric));
			Assert::AreEqual(1, tzHourResult);

			char* TZMinuteNotNumeric = "2025-08-04T10:52:00-05:^^";
			int tzMinuteResult = validate_datetime_string_format(TZMinuteNotNumeric, strlen(TZMinuteNotNumeric));
			Assert::AreEqual(1, tzMinuteResult);

			char* wrongUTCLetter= "2025-08-04T10:52:00z"; //we think lower case is bad right?
			int wrongUTCResult = validate_datetime_string_format(wrongUTCLetter, strlen(wrongUTCLetter));
			Assert::AreEqual(1, wrongUTCResult);

			char* switchColonsAndDashes= "2025:08:04T10-52-00:05-00";
			int wrongDashes = validate_datetime_string_format(switchColonsAndDashes, strlen(switchColonsAndDashes));
			Assert::AreEqual(1, wrongDashes);
			
			char* emptyString = "";
			int emptyResult = validate_datetime_string_format(emptyString, strlen(emptyString));
			Assert::AreEqual(1, emptyResult);
			
			char* twoGoodDatesInARow= "2025-08-04T10:52:00-05:002025-08-04T10:52:00-05:00";
			int twoResult = validate_datetime_string_format(twoGoodDatesInARow, strlen(twoGoodDatesInARow));
			Assert::AreEqual(1, twoResult);
			
			char* cutshort = "2025-08-04T10:52:0";
			int cutResult = validate_datetime_string_format(cutshort, strlen(cutshort));
			Assert::AreEqual(1, cutResult);
		}
	};
}
