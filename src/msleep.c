#include <msleep.h>
#include <time.h>

int msleep(long msec) {
    struct timespec ts; int res;
    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;
    while ((res = nanosleep(&ts, &ts)));
    return res;
}
