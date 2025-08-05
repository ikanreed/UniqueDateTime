#include <stdio.h>
#include "DateTimeStruct.h"
#include "StringHelper.h"
#include "string.h"

//way more than the size of a datetime, but potentially less than really stupid edge cases
#define MAX_LINE_LENGTH 100

int main(int args, char** argv)
{
	char cleaned_buffer[MAX_LINE_LENGTH];
	char lineBuffer[MAX_LINE_LENGTH];
	while (scanf_s("%[^\n]", lineBuffer, MAX_LINE_LENGTH)!= EOF)
	{
		
		trimstring(lineBuffer, MAX_LINE_LENGTH, cleaned_buffer);
		
		struct DateTime parsed;
		int validationResult = parse_datetime(cleaned_buffer, MAX_LINE_LENGTH, &parsed);


		if (validationResult != 0)
		{
			//only report non-empty lines as problems
			if (strcmp(cleaned_buffer, "") != 0)
			{
				fprintf(stderr, "Invalid date: %s, error code: %i", cleaned_buffer, validationResult);
			}
		}
		//good dates get checked into the btree
		else
		{
			//todo: insert into tree, print if new
		}
	}
}