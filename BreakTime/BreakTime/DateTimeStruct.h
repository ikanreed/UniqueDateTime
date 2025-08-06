#pragma once
//this is for the visual c++ test project and doesn't impact the C code
#ifdef __cplusplus
extern "C" {  // only need to export C interface if
	// used by C++ source code
#endif

struct DateTime
{
	unsigned short year;
	unsigned char month;
	char day;
	char hour;
	char minute;
	char second;
	signed char tz_hour;
	char tz_minutes;
};

#define DT_VALID 0
#define DT_INVALID_STRING_FORMAT 1
#define DT_INVALID_MONTH 2
#define DT_INVALID_DAY 3
#define DT_INVALID_HOUR 4
#define DT_INVALID_MINUTE 5
#define DT_INVALID_SECONDS 6
#define DT_INVALID_TZ 7

int validate_datetime_string_format(char* datestring, int str_length);

int parse_datetime(char* datestring, int str_length, struct DateTime* result);

int compare_raw_values(void* leftDT, void* rightDT);

#ifdef __cplusplus
}
#endif