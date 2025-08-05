#include "DateTimeStruct.h"
#include "StringHelper.h"


int RequireDigit(char* string, int index)
{
	char characterAtIndex = string[index];
	if (characterAtIndex >= '0' && characterAtIndex <= '9')
	{
		return 0;
	}
	return 1;
}
int RequireValue(char* string, int index, char value)
{
	char characterAtIndex = string[index];
	if (characterAtIndex == value)
	{
		return 0;
	}
	return 1;
}

/// <summary>
/// Checks that the basic format of the string to be parsed is correct
/// </summary>
/// <param name="datestring">The string to be validated</param>
/// <param name="str_length">the length of the string passed</param>
/// <returns>0 if potentially valid, non-zero if invalid.</returns>
int validate_datetime_string_format(char* datestring, int str_length)
{
	//There are only two valid post-trimming lengths for datetimes.  Those with a +/- HH:MM and those with just Z at the end
	if (str_length != 20 && str_length != 25)
	{
		return 1;
	}
	int invalid = 0;
	
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
			invalid |= 1;
		}
		invalid |= RequireDigit(datestring, 20);
		invalid |= RequireDigit(datestring, 21);
		invalid |= RequireValue(datestring, 22, ':');
		invalid |= RequireDigit(datestring, 23);
		invalid |= RequireDigit(datestring, 24);
	}



	return invalid;
}

/// <summary>
/// Parses a datetime and writes the result to a passed argument
/// </summary>
/// <param name="datestring">a string containing the date</param>
/// <param name="str_length">the length of datestring in bytes</param>
/// <param name="result">(out) the structure to fill</param>
/// <returns>0 if succesful, non-zero if unsuccesful</returns>
int parse_datetime(char* datestring, int str_length, struct DateTime* result)
{
	return 1;
}