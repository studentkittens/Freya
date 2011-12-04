/*  Sample test */
#include <cxxtest/TestSuite.h>
#include "Writer.hh"

/* The whole suite. One suit for each module. */
class LogTestSuite : public CxxTest::TestSuite
{
    public:
        /* A testcase == a method */
        void testAddition( void )
        {
            TS_ASSERT( 1 + 1 > 1 );
            TS_ASSERT_EQUALS( 1 + 1, 2 );

            /* Test if linking works */
            Log::Writer& bla = Log::Writer::instance();
        }




};
