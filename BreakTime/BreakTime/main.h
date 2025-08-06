#pragma once

void RunMainLoop(FILE* infile, FILE* outfile);

void ReportBadDate(char*  cleaned_buffer, int validationResult);

void WriteIfUnique(BinaryTree** tree, struct DateTime* parsedRef, char* date_text, FILE* outfile);
