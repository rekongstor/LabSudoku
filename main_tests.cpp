#define BOOST_TEST_MODULE My Test 
#define BOOST_TEST_NO_MAIN
#define BOOST_TEST_ALTERNATIVE_INIT_API
#include <boost/test/included/unit_test.hpp> 

bool is_negative(int i)
{
	return i < 0;
}

BOOST_AUTO_TEST_CASE(first_test) 
{
	int i = 1;
	BOOST_TEST(i); 
	BOOST_TEST(i == 2); 
}

BOOST_AUTO_TEST_CASE(second_test)
{
	BOOST_TEST(is_negative(0));
	BOOST_TEST(is_negative(1));
	BOOST_TEST(is_negative(-1));
}


int EntryPoint();

int main(int argc, char** argv)
{
    // prototype for user's unit test init function
#ifdef BOOST_TEST_ALTERNATIVE_INIT_API
    extern bool init_unit_test();

    boost::unit_test::init_unit_test_func init_func = &init_unit_test;
#else
    extern ::boost::unit_test::test_suite* init_unit_test_suite( int argc, char* argv[] );

    boost::unit_test::init_unit_test_func init_func = &init_unit_test_suite;
#endif
    int k = boost::unit_test::unit_test_main( init_func, argc, argv );

	system("pause");
	return k;
}