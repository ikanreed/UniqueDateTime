#include "string.h"
#include "StringHelper.h"
#include <stdlib.h>
#include <stdio.h>


//this should be in a mathish h file, but considering the scope the project the creep was just too much
#define MIN(a,b) (((a)<(b))?(a):(b))

int IsWhitespace(char c)
{
	switch (c)
	{
	case ' ':
	case '\t':
	case '\r':
	case '\n':
		return 1;
	default:
		return 0;
	}
}

/// <summary>
/// Creates a new string containing the trimmedString with leading and trailing whitespace removed
/// </summary>
/// <param name="trimmedString">the string to be trimmed</param>
/// <param name="length">the buffer size of trimmedString</param>
/// <param name="resultString">(out)pointer to newly allocated string</param>
/// <param name="resultLength">(out)pointer to value to assign length</param>
void trimstring(char* trimmedString, int length, char** resultString, int* resultLength)
{
	int start = 0;
	//if our buffer is longer than the null terminated string, let's cut that off too
	int end = MIN(strlen(trimmedString), length) - 1;

	while (start < length && IsWhitespace(trimmedString[start]))
	{
		start++;
	}

	while (end > start && (IsWhitespace(trimmedString[end]) || trimmedString[end] == 0))
	{
		end--;
	}
	*resultLength= end + 2-start;
	//I know sizeof(char) is redundant, but we live in 2025, and UTF8-readiness is just sensible

	char* result= (char *)malloc(sizeof(char) * (*resultLength));
	result[*resultLength-1] = 0;//null terminate our new string
	for (int i = start; i <= end; i++)
	{
		result[i - start] = trimmedString[i];
	}
	*resultString = result;
}


