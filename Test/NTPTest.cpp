#include <UnitTest++/UnitTest++.h>
#include "../ntp/NTP.h"

struct __fixture
{
    NTP ntp = NTP({"ntp21.vniiftri.ru"});
};

static const uint64_t ntp_time0 = 16211417784729168930U;
static const timespec time0 = {.tv_sec = 1565526037, .tv_nsec = 360281714};

SUITE(TimeConvertTest)
{
    TEST(TimespecToNtpConvertTest)
    {
        uint64_t ntp;
        ts_to_ntp(ntp, &time0);
        CHECK_CLOSE(ntp, ntp_time0, 5);
    }

    TEST(NtpToTimespecConvertTest)
    {
        timespec tp;
        ntp_to_ts(ntp_time0, &tp);
        CHECK_EQUAL(tp.tv_sec, time0.tv_sec);
        CHECK_CLOSE(tp.tv_nsec, time0.tv_nsec, 1);
    }
}

SUITE(GetTimeDiffTest)
{
    TEST_FIXTURE(__fixture, GetTimeDiffTest1)
    {
        timespec tp;
        int64_t diff = ntp.get_time_diff();
        CHECK_CLOSE(diff, 0, 429496730);
    }

    TEST_FIXTURE(__fixture, GetTimeDiffTest2)
    {
        timespec tp;
        clock_gettime(CLOCK_REALTIME, &tp);
        tp.tv_sec += 1073741823;
        clock_settime(CLOCK_REALTIME, &tp);
        int64_t diff = ntp.get_time_diff();
        CHECK_CLOSE(diff, -4611686014132420608, 8589934592);
        tp.tv_sec -= 1073741823;
        clock_settime(CLOCK_REALTIME, &tp);
    }

    TEST_FIXTURE(__fixture, GetTimeDiffTest3)
    {
        timespec tp;
        clock_gettime(CLOCK_REALTIME, &tp);
        tp.tv_sec -= 1073741823;
        clock_settime(CLOCK_REALTIME, &tp);
        int64_t diff = ntp.get_time_diff();
        CHECK_CLOSE(diff, 4611686014132420608, 8589934592);
        tp.tv_sec += 1073741823;
        clock_settime(CLOCK_REALTIME, &tp);
    }
}

SUITE(TimeSyncTest)
{
    TEST_FIXTURE(__fixture, TimeSyncTest1)
    {
        timespec tp1, tp2;
        clock_gettime(CLOCK_REALTIME, &tp1);
        tp2.tv_sec = tp1.tv_sec + 1073741823;
        tp2.tv_nsec = tp1.tv_nsec;
        clock_settime(CLOCK_REALTIME, &tp2);
        ntp.sync();
        clock_gettime(CLOCK_REALTIME, &tp2);
        CHECK_CLOSE(tp1.tv_sec, tp2.tv_sec, 2);
    }

    TEST_FIXTURE(__fixture, TimeSyncTest2)
    {
        timespec tp1, tp2;
        clock_gettime(CLOCK_REALTIME, &tp1);
        tp2.tv_sec = tp1.tv_sec + 1073741823;
        tp2.tv_nsec = tp1.tv_nsec;
        clock_settime(CLOCK_REALTIME, &tp2);
        time_t t = ntp.sync();
        CHECK_CLOSE(t, tp1.tv_sec, 2);
    }
}