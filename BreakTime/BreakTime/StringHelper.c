#include "string.h"
#include "StringHelper.h"
#include <stdlib.h>
#include <stdio.h>




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
/// <param name="resultString">(out)buffer for new string, should be at least length in size</param>
void trimstring(char* trimmedString, int length, char* resultBuffer)
{
	int start = 0;
	//if our buffer is longer than the null terminated string, let's cut that off too
	int end = (int)MIN(strlen(trimmedString), length) - 1;

	while (start < length && IsWhitespace(trimmedString[start]))
	{
		start++;
	}

	while (end > start && (IsWhitespace(trimmedString[end]) || trimmedString[end] == 0))
	{
		end--;
	}
	int resultLength= end + 2-start;

	resultBuffer[resultLength-1] = 0;//null terminate our new string
	for (int i = start; i <= end; i++)
	{
		resultBuffer[i - start] = trimmedString[i];
	}
}

/// <summary>
/// Gets a integer from a set number of digits
/// </summary>
/// <param name="string">A string to parse numbers from</param>
/// <param name="start">The index of the first number</param>
/// <param name="numdigits">the number of digits to parse</param>
/// <returns>The value</returns>
int parseint(char* string, int start, int numdigits)
{
	//in a world where the string isn't prevalidated, I'd want this to have a better signature that allows for parsing failure
	int curValue = 0;
	for (int i = 0; i < numdigits; i++)
	{
		curValue *= 10;
		int curDigit = string[start + i] - '0';
		curValue += curDigit;
	}
	return curValue;
}


