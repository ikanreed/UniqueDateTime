#include "DateTimeStruct.h"
#include "StringHelper.h"


int RequireDigit(char* string, int index)
{
	char characterAtIndex = string[index];
	if (characterAtIndex >= '0' && characterAtIndex <= '9')
	{
		return DT_VALID;
	}
	return DT_INVALID_STRING_FORMAT;
}
int RequireValue(char* string, int index, char value)
{
	char characterAtIndex = string[index];
	if (characterAtIndex == value)
	{
		return DT_VALID;
	}
	return DT_INVALID_STRING_FORMAT;
}


/// <summary>
/// Checks that the basic format of the string to be parsed is correct
/// </summary>
/// <param name="datestring">The string to be validated</param>
/// <param name="str_length">the length of the string passed</param>
/// <returns>0 if potentially valid, non-zero if invalid.</returns>
int validate_datetime_string_format(char* datestring, int buffer_size)
{
	int str_length = MIN(strlen(datestring), buffer_size);
	
	//There are only two valid post-trimming lengths for datetimes.  Those with a +/- HH:MM and those with just Z at the end
	if (str_length != 20 && str_length != 25)
	{
		return DT_INVALID_STRING_FORMAT;
	}
	int invalid = DT_VALID;
	
	//year
	invalid |= RequireDigit(datestring, 0);
	invalid |= RequireDigit(datestring, 1);
	invalid |= RequireDigit(datestring, 2);
	invalid |= RequireDigit(datestring, 3);

	invalid |= RequireValue(datestring, 4, '-');
	//month
	invalid |= RequireDigit(datestring, 5);
	invalid |= RequireDigit(datestring, 6);

	invalid |= RequireValue(datestring, 7, '-');
	//day
	invalid |= RequireDigit(datestring, 8);
	invalid |= RequireDigit(datestring, 9);

	invalid |= RequireValue(datestring, 10, 'T');
	//hour
	invalid |= RequireDigit(datestring, 11);
	invalid |= RequireDigit(datestring, 12);
	
	invalid |= RequireValue(datestring, 13, ':');
	//minute
	invalid |= RequireDigit(datestring, 14);
	invalid |= RequireDigit(datestring, 15);

	invalid |= RequireValue(datestring, 16, ':');
	//second
	invalid |= RequireDigit(datestring, 17);
	invalid |= RequireDigit(datestring, 18);

	if (str_length == 20)
	{
		invalid |= RequireValue(datestring, 19, 'Z');
	}
	if (str_length == 25)
	{
		char plusMinus = datestring[19];
		if (plusMinus != '-' && plusMinus != "+")
		{
			invalid |= DT_INVALID_STRING_FORMAT;
		}
		invalid |= RequireDigit(datestring, 20);
		invalid |= RequireDigit(datestring, 21);
		invalid |= RequireValue(datestring, 22, ':');
		invalid |= RequireDigit(datestring, 23);
		invalid |= RequireDigit(datestring, 24);
	}



	return invalid;
}



int validate_datetime(struct DateTime* datetime)
{
	if (datetime->month < 1 || datetime->month>12)
		return DT_INVALID_MONTH;
	if (datetime->day < 1 || datetime->day>31)
		return DT_INVALID_DAY;
	if (datetime->hour < 0 || datetime->hour>23)
		return DT_INVALID_HOUR;
	if (datetime->minute < 0 || datetime->minute>59)
		return DT_INVALID_MINUTE;
	if (datetime->second < 0 || datetime->second>59)
		return DT_INVALID_SECONDS;
	//we're going to assume that post IDL time zones could hypothetically go all the way around the world even though +13 is as high as they are in the real world
	if (datetime->tz_hour < -24 || datetime->tz_hour>24 || datetime->tz_minutes < -59 || datetime->tz_minutes>59)
		return DT_INVALID_TZ;
	return DT_VALID;
}

/// <summary>
/// Parses a datetime and writes the result to a passed argument
/// </summary>
/// <param name="datestring">a string containing the date</param>
/// <param name="str_length">the length of datestring buffer in bytes</param>
/// <param name="result">(out) the structure to fill</param>
/// <returns>0 if succesful, non-zero if unsuccesful</returns>
int parse_datetime(char* datestring, int str_length, struct DateTime* result)
{
	int string_validation_result = validate_datetime_string_format(datestring, str_length);
	if (string_validation_result != DT_VALID)
	{
		return string_validation_result;
	}
	//I tried this with fewer magic numbers and it ended up being harder to read rather than easier.
	//the maintainability is lower, but I think if date formats start changing a lot the requirements should be handled by different code
	result->year = parseint(datestring, 0, 4);
	result->month = parseint(datestring, 5, 2);
	result->day = parseint(datestring, 8, 2);
	
	result->hour = parseint(datestring, 11, 2);
	result->minute = parseint(datestring, 14, 2);
	result->second = parseint(datestring, 17, 2);

	if (datestring[19] == 'Z')
	{
		result->tz_hour = 0;
		result->tz_minutes = 0;
	}
	else
	{
		result->tz_hour = parseint(datestring,20, 2);
		result->tz_minutes = parseint(datestring, 23, 2);
		if (datestring[19] == '-')
		{
			result->tz_hour *= -1;
			//this minutes choice specifically affects if we want unique TIMES rather than unique timeSTAMPS
			result->tz_minutes *= -1;
		}
	}
	return validate_datetime(result);

}