#include <stdio.h>
#include "DateTimeStruct.h"
#include "StringHelper.h"
#include "string.h"
#include "BinaryTree.h"
#include "main.h"

//way more than the size of a datetime, but potentially less than really stupid edge cases
#define MAX_LINE_LENGTH 100


int main(int args, char** argv)
{
	//TODO: parse args for alternative inputs and outputs, we're doing this POSIX style 
	//TODO: allow args for alternative comparison methods(unique dates, unique times, force all dates to UTC, etc)
	return RunMainLoop(stdin, stdout);
}

int RunMainLoop(FILE* infile, FILE* outfile)
{
	char cleaned_buffer[MAX_LINE_LENGTH];
	char lineBuffer[MAX_LINE_LENGTH];
	BinaryTree* alreadyFound = 0;
	int numberOfDates = 0;
	int returnCode = 0;
	int scanfresult;
	while (scanfresult=fscanf_s(infile, "%[^\n]", lineBuffer, MAX_LINE_LENGTH) != EOF)
	{
		//consume the newline.  
		fgetc(infile);
		trimstring(lineBuffer, MAX_LINE_LENGTH, cleaned_buffer);

		struct DateTime parsed;
		int validationResult = parse_datetime(cleaned_buffer, MAX_LINE_LENGTH, &parsed);


		if (validationResult != DT_VALID)
		{
			returnCode = 1;
			ReportBadDate(cleaned_buffer, validationResult);
		}
		//good dates get checked into the btree
		else
		{
			numberOfDates++;
			WriteIfUnique(&alreadyFound, &parsed, cleaned_buffer, outfile);
			//TODO: periodically balance the tree for very large datasets that are already ordered.  If we wanted O(N) insertion, we'd use an array set.
		}
		
	}
	//let's allow this to be not the main of every program that uses it, and free our malloc'd memory
	free_tree(alreadyFound);
	//if we're going for a posix-style app, we should exit with non-zero if anything went wrong.
	//don't break shell scripting assumptions
	return returnCode;
}

void WriteIfUnique(BinaryTree** tree, struct DateTime* parsedRef, char* date_text, FILE* outfile)
{
	int isNew = 0;
	if (*tree == 0)
	{
		//if it's our first date, it's definetly new, make a tree, write it to output
		*tree = new_tree(parsedRef, sizeof(struct DateTime));
		isNew = 1;
	}
	else
	{
		isNew = tree_insert(*tree, parsedRef, sizeof(struct DateTime), &compare_raw_values);
	}
	if (isNew)
	{
		//for now we'll write it as we recieved it, except with whitespace removed.
		//there's other cases to consider: e.g. do we want to normalize UTC to Z or +00:00?
		//TODO: skip this if we're printing sorted output, rather than prioritizing "feeding" downpipe program
		fprintf(outfile, "%s\n", date_text);
	}
}


void ReportBadDate(char*  cleaned_buffer, int validationResult)
{
	//only report non-empty lines as problems
	if (strcmp(cleaned_buffer, "") != 0)
	{
		switch (validationResult)
		{
		case DT_INVALID_STRING_FORMAT:
			fprintf(stderr, "Bad date format: %s\n", cleaned_buffer);
			break;
		case DT_INVALID_MONTH:
			fprintf(stderr, "Invalid month: %s\n", cleaned_buffer);
			break;
		case DT_INVALID_DAY:
			fprintf(stderr, "Invalid day: %s\n", cleaned_buffer);
			break;
		case DT_INVALID_HOUR:
		case DT_INVALID_MINUTE:
		case DT_INVALID_SECONDS:
			fprintf(stderr, "Invalid time: %s\n", cleaned_buffer);
			break;
		case DT_INVALID_TZ:
			fprintf(stderr, "Invalid time zone: %s\n", cleaned_buffer);
			break;
		default:
			fprintf(stderr, "Invalid datetime: %s, error code: %i\r\n", cleaned_buffer, validationResult);
		}

	}
}
