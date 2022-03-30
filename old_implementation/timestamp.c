#include "timestamp.h"

#include <time.h>

#if defined(USE_TIMESPEC) && USE_TIMESPEC

#include <stdbool.h>

/*
 * NOTE
 * If for some reasons `timespec_get` and `clock_gettime` do not exist on your system
 * go to the header `timestamp.h` and change the #define to:
 *
 * #define USE_TIMESPEC (0)
 *
 * This will make use of a fallback function `time()` which works just about on every system.
 * (But your timestamps will have only 1s resolution instead of 1us.)
 *
 */

static _Bool get_timepoint(struct timespec *ts) {
#if defined(_MSC_VER)
    if(timespec_get(ts, TIME_UTC) == TIME_UTC) {
             return true;
         }
#else
    if(clock_gettime(CLOCK_REALTIME, ts) == 0) {
          return true;
      }
#endif
    return false;
}


long long get_timestamp(){
    // Note: if for some reasons `get_timepoint` doesn't work
    struct timespec ts;
    if (get_timepoint(&ts)){
        return ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    }
    return 0;
}

#else
long long get_timestamp(){
    time_t ts = time(NULL);
    return (long long)ts;
}

#endif