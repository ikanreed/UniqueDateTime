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
			Assert::AreEqual(DT_VALID, goodResult);
			
			char* UTCTz = "2025-08-04T10:52:00Z";
			int UTCresult = validate_datetime_string_format(UTCTz, strlen(UTCTz));
			Assert::AreEqual(DT_VALID, UTCresult);


			char* yearNotNumeric = "20A5-08-04T10:52:00-05:00";
			int yearNotNumericResult = validate_datetime_string_format(yearNotNumeric, strlen(yearNotNumeric));
			//for now all our invalid string error codes are 1
			Assert::AreEqual(DT_INVALID_STRING_FORMAT, yearNotNumericResult);

			char* monthNotNumeric = "2025-{8-04T10:52:00-05:00";
			int monthNotNumericResult = validate_datetime_string_format(monthNotNumeric, strlen(monthNotNumeric));
			//for now all our invalid string error codes are 1
			Assert::AreEqual(DT_INVALID_STRING_FORMAT, monthNotNumericResult);

			char* dayNotNumeric = "2025-08-0*T10:52:00-05:00";
			int dayResult = validate_datetime_string_format(dayNotNumeric, strlen(dayNotNumeric));
			//for now all our invalid string error codes are 1
			Assert::AreEqual(DT_INVALID_STRING_FORMAT, dayResult);

			char* hourNotNumeric = "2025-08-04T1P:52:00-05:00";
			int hourResult = validate_datetime_string_format(hourNotNumeric, strlen(hourNotNumeric));
			Assert::AreEqual(DT_INVALID_STRING_FORMAT, hourResult);

			char* minuteNotNumeric = "2025-08-04T10:5X:00-05:00";
			int minuteResult = validate_datetime_string_format(minuteNotNumeric, strlen(minuteNotNumeric));
			Assert::AreEqual(DT_INVALID_STRING_FORMAT, minuteResult);

			char* secondNotNumeric = "2025-08-04T10:52:0I-05:00";
			int secondResult = validate_datetime_string_format(secondNotNumeric, strlen(secondNotNumeric));
			Assert::AreEqual(DT_INVALID_STRING_FORMAT, secondResult);

			char* TZHourNotNumeric = "2025-08-04T10:52:00-O5:00";
			int tzHourResult = validate_datetime_string_format(TZHourNotNumeric, strlen(TZHourNotNumeric));
			Assert::AreEqual(DT_INVALID_STRING_FORMAT, tzHourResult);

			char* TZMinuteNotNumeric = "2025-08-04T10:52:00-05:^^";
			int tzMinuteResult = validate_datetime_string_format(TZMinuteNotNumeric, strlen(TZMinuteNotNumeric));
			Assert::AreEqual(DT_INVALID_STRING_FORMAT, tzMinuteResult);

			char* wrongUTCLetter= "2025-08-04T10:52:00z"; //we think lower case is bad right?
			int wrongUTCResult = validate_datetime_string_format(wrongUTCLetter, strlen(wrongUTCLetter));
			Assert::AreEqual(DT_INVALID_STRING_FORMAT, wrongUTCResult);

			char* switchColonsAndDashes= "2025:08:04T10-52-00:05-00";
			int wrongDashes = validate_datetime_string_format(switchColonsAndDashes, strlen(switchColonsAndDashes));
			Assert::AreEqual(DT_INVALID_STRING_FORMAT, wrongDashes);
			
			char* emptyString = "";
			int emptyResult = validate_datetime_string_format(emptyString, strlen(emptyString));
			Assert::AreEqual(DT_INVALID_STRING_FORMAT, emptyResult);
			
			char* twoGoodDatesInARow= "2025-08-04T10:52:00-05:002025-08-04T10:52:00-05:00";
			int twoResult = validate_datetime_string_format(twoGoodDatesInARow, strlen(twoGoodDatesInARow));
			Assert::AreEqual(DT_INVALID_STRING_FORMAT, twoResult);
			
			char* cutshort = "2025-08-04T10:52:0";
			int cutResult = validate_datetime_string_format(cutshort, strlen(cutshort));
			Assert::AreEqual(DT_INVALID_STRING_FORMAT, cutResult);
		}

		TEST_METHOD(TestParseDatetime)
		{
			struct DateTime parsed;
			int success;
			success = parse_datetime("2025-08-04T10:52:01-05:25", 25, &parsed);
			Assert::AreEqual(DT_VALID, success);
			Assert::AreEqual(2025, (int)parsed.year);
			Assert::AreEqual(8, (int)parsed.month);
			Assert::AreEqual(4, (int)parsed.day);
			Assert::AreEqual(10, (int)parsed.hour);
			Assert::AreEqual(52, (int)parsed.minute);
			Assert::AreEqual(1, (int)parsed.second);
			Assert::AreEqual(-5, (int)parsed.tz_hour);
			Assert::AreEqual(-25, (int)parsed.tz_minutes);


			success = parse_datetime("2025-20-04T10:52:01-05:25", 25, &parsed);
			Assert::AreEqual(DT_INVALID_MONTH, success);


			success = parse_datetime("0001-01-01T00:00:00Z", 25, &parsed);
			Assert::AreEqual(DT_VALID, success);
			Assert::AreEqual(0, (int)parsed.tz_hour);
			Assert::AreEqual(0, (int)parsed.tz_minutes);
		}
	};
}
