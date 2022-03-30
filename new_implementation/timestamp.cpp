//
// Created by hello on 28/03/2022.
//

#include "timestamp.h"

#if defined(USE_TIMESPEC) && USE_TIMESPEC

static bool get_timepoint (struct timespec *ts) {
#if defined (_MSC_VER)
    if (timespec_get (ts, TIME_UTC) == TIME_UTC) {
        return true;
    }
#else
    if (clock_gettime (CLOCK_REALTIME, ts) == 0) {
        return true;
    }
#endif
    return false;
}


long long get_timestamp () {
    struct timespec ts {};
    if (get_timepoint (&ts)){
        return ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    }
    return 0;
}

#else
static long long get_timestamp (){
    time_t ts = time(nullptr);
    return (long long)ts;
}

#endif
