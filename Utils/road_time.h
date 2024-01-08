/// @file
/// @author  Danilo Alves de Lima
/// @date    December, 2018
/// @brief Brief description.
///
/// Detailed description.

#ifndef DEF_ROAD_TIME_H
#define DEF_ROAD_TIME_H

#include <stddef.h>  // defines: NULL
#include <stdint.h>
#include <sys/time.h>

/// Timestamp type
typedef uint64_t road_time_t;
/// Timerange type
typedef int32_t road_timerange_t;

/// Timestamp difference type
typedef int64_t road_time_diff_t;
/// Timerange difference type
typedef int32_t road_timerange_diff_t;

static road_time_t road_time(void)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return(road_time_t)((road_time_t)(t.tv_sec)*1000000 + (road_time_t)(t.tv_usec));
}

#endif // DEF_ROAD_TIME_H
