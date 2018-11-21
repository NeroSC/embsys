// Question 8 : write here the buggy function without errors
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "../gps/src/lib/nmea/nmea.h"

#define KNOT_TO_KMH 1.852

int iteration = 0;

int knot_to_kmh_str(float not, size_t size, char * format, char * kmh_str)
{
    float kmh = KNOT_TO_KMH * not;
    snprintf(kmh_str, size, format, kmh);

#ifndef GPS_OK
    iteration++;
    if (iteration == 2)
    {
        //char* empty = NULL;
        puts("");
    }
#endif

    return kmh;
}

int printf(const char *format, ...){

    
}
// Question 12 : write printf with a signal handler

