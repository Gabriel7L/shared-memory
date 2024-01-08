
#ifndef TEST_STRUCT
#define TEST_STRUCT

#include <stdint.h>
#include <string>

typedef struct
{
	uint8_t digital;//|Not_Used|Not_Used|Not_Used|Button1|Button2|Button3|Led1|Led2
	uint16_t pot1;
	uint16_t pot2;
	uint16_t pot3;
	uint16_t pot4;
	uint8_t led3;
	uint8_t led4;
	
}TEST_DATA;

typedef struct
{
	road_time_t time;
	TEST_DATA data;
}Timestamped_TEST_DATA;

#endif
