#include "DateTimeStruct.h"
#include "StringHelper.h"

/// <summary>
/// Checks that the basic format of the string to be parsed is correct
/// </summary>
/// <param name="datestring">The string to be validated</param>
/// <param name="str_length">the length of the string passed</param>
/// <returns>0 if potentially valid, non-zero if invalid.</returns>
int validate_datetime_string_format(char* datestring, int str_length)
{
	//todo: basic implementation
	return 1;
}

int parse_datetime(char* datestring, int str_length, struct DateTime* result)
{
	return 1;
}