#pragma once

//this should be in a mathish h file, but considering the scope the project the creep was just too much
#define MIN(a,b) (((a)<(b))?(a):(b))

void trimstring(char* trimmedString, int length, char* resultBuffer);

int parseint(char* string, int start, int numdigits);

