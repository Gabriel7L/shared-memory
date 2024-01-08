#ifndef NLMT_STRUCT
#define NLMT_STRUCT

#include <stdint.h>
#include <string>
#include "../Utils/road_time.h"

namespace NLMT {
	
typedef struct 
{
	
	float iTOW;

	float lon;

	float lat;

	float heigth;

	float hMLS;

	float hAcc;

	float vAcc;

}GPS_DATA;

typedef struct
{
    road_time_t time;
    
    GPS_DATA data;
} Timestamped_GPS_DATA;

}
#endif
