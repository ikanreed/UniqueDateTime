#include "DatetimeStruct.h"

int compare_raw_values(void* leftDT, void* rightDT)
{
	struct DateTime* left = (struct DateTime*)leftDT;
	struct DateTime* right = (struct DateTime*)rightDT;
	//clear the pointer comparisons first
	if (left == 0 && right==0)
		return 0;
	if (left == 0)
		return 1;
	if (right == 0)
		return -1;
	int diff;
	
	diff=left->year - right->year;
	if (diff != 0)
		return diff;
	diff = left->month - right->month;
	if (diff != 0)
		return diff;
	diff = left->day - right->day;
	if (diff != 0)
		return diff;
	diff = left->hour - right->hour;
	if (diff != 0)
		return diff;
	diff = left->minute - right->minute;
	if (diff != 0)
		return diff;
	diff = left->second - right->second;
	if (diff != 0)
		return diff;
	diff = left->tz_hour- right->tz_hour;
	if (diff != 0)
		return diff;
	diff = left->tz_minutes - right->tz_minutes;
	if (diff != 0)
		return diff;
	return 0;

}