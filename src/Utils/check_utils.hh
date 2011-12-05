#ifndef FREYA_CXX_UTILS_GUARD
#define FREYA_CXX_UTILS_GUARD

#include "Utils.hh"

class UtilsTestSuite : public CxxTest::TestSuite
{

    public:
//-------------------------------------------------------------
// Utils::seconds_to_duration(unsinged long)
        void testseconds_to_duration_1_year(void)
        {
            TS_ASSERT("52 weeks 1 days 0 hours 0 minutes 0 seconds" == Utils::seconds_to_duration(60/*seconds*/ * 60/*minutes*/ * 24/*hours*/ * 365/*days*/));
        }
        void testseconds_to_duration_check_if_always_the_same(void)
        {
            TS_ASSERT(Utils::seconds_to_duration(60*60*24*365) == Utils::seconds_to_duration(60*60*24*365));
        }
        void testseconds_to_duration_1_second(void)
        {
            TS_ASSERT("0 hours 0 minutes 1 seconds" == Utils::seconds_to_duration(1));
        }
        void testseconds_to_duration_0_seconds(void)
        {
            TS_ASSERT("0 hours 0 minutes 0 seconds" == Utils::seconds_to_duration(0));
        }
        void testseconds_to_duration_1_minutes(void)
        {
            TS_ASSERT("0 hours 1 minutes 0 seconds" == Utils::seconds_to_duration(60));
        }
        void testseconds_to_duration_2_minutes(void)
        {
            TS_ASSERT("0 hours 2 minutes 0 seconds" == Utils::seconds_to_duration(120));
        }
        void testseconds_to_duration_1_hour(void)
        {
            TS_ASSERT("1 hours 0 minutes 0 seconds" == Utils::seconds_to_duration(3600));
        }
        void testseconds_to_duration_2_hours(void)
        {
            TS_ASSERT("2 hours 0 minutes 0 seconds" == Utils::seconds_to_duration(7200));
        }
        void testseconds_to_duration_1_day(void)
        {
            TS_ASSERT("1 days 0 hours 0 minutes 0 seconds" == Utils::seconds_to_duration(3600*24));
        }
        void testseconds_to_duration_2_days(void)
        {
            TS_ASSERT("2 days 0 hours 0 minutes 0 seconds" == Utils::seconds_to_duration(2*3600*24));
        }
        void testseconds_to_duration_2_years(void)
        {
            TS_ASSERT("104 weeks 2 days 0 hours 0 minutes 0 seconds" == Utils::seconds_to_duration(2*60*60*24*365));
        }


//-------------------------------------------------------------
//  Utils::seconds_to_timestamp(const long)
        void testseconds_to_timestamp_date1(void)
        {
            TS_ASSERT("2011-12-05" == Utils::seconds_to_timestamp(1323039600));
        }
};




#endif
