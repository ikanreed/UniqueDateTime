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

int validate_datetime_string_format(char* datestring, int str_length);

int parse_datetime(char* datestring, int str_length, struct DateTime* result);

#ifdef __cplusplus
}
#endif