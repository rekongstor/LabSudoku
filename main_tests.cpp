#define BOOST_TEST_MODULE My Test 
#define BOOST_TEST_NO_MAIN
#define BOOST_TEST_ALTERNATIVE_INIT_API
#include <boost/test/included/unit_test.hpp> 
#include <boost/test/output_test_stream.hpp>

#include "src/sudoku.h"
#include "src/cell.h"
#include "src/workgroup.h"


BOOST_AUTO_TEST_CASE(Cell_Tests) 
{
	cell c;
	BOOST_TEST(*c==0); 
	BOOST_TEST(+c==9); 
	c^=0;
	BOOST_TEST(+c==8);
	c^=0;
	BOOST_TEST(+c==8);
	c^=1;
	BOOST_TEST(+c==7);
	u8 eg[] = {1,0,1,0,0,0,0,0,0};
	c-eg;
	BOOST_TEST(+c==6);
	c=5;
	BOOST_TEST(*c==5);
	BOOST_TEST(+c==0);
}

BOOST_AUTO_TEST_CASE(Workgroup_Tests)
{
	cell c[9];
	c[5] = 1;
	cell* cs[9];
	for (u8 i=0;i<9;++i)
		cs[i]=&c[i];
	
	workgroup wg(cs,(u8)5);
	BOOST_TEST(wg.is_empty()==true);
	BOOST_TEST(wg.iterate_mask()==true);
	BOOST_TEST(wg.is_empty()==false);
	BOOST_TEST(wg.calculate_wg()==false);
	workgroup wg2(cs,(u8)8);
	BOOST_TEST(wg2.iterate_mask()==true);
	BOOST_TEST(wg2.iterate_mask()==true);
	BOOST_TEST(wg2.iterate_mask()==true);
	BOOST_TEST(wg2.iterate_mask()==true);
	BOOST_TEST(wg2.iterate_mask()==true);
	BOOST_TEST(wg2.iterate_mask()==true);
	BOOST_TEST(wg2.iterate_mask()==true);
	BOOST_TEST(wg2.iterate_mask()==true);
	BOOST_TEST(wg2.iterate_mask()==false);

	
}

BOOST_AUTO_TEST_SUITE(Sudoku_Tests_Suite)
class cout_redirect 
{
	std::streambuf* old;
public:
	cout_redirect(std::streambuf* new_buffer): old(std::cout.rdbuf(new_buffer)){};
	~cout_redirect(){std::cout.rdbuf(old);};
};

BOOST_AUTO_TEST_CASE(Sudoku_Tests)
{
	sudoku s;
	s.load_file("input3.txt");
	s.calculate_all();
	boost::test_tools::output_test_stream output;
	{
		cout_redirect guard(output.rdbuf());
		s.print();
	}
	BOOST_CHECK(output.is_equal(
	"1 3 2 8 6 5 4 7 9 \n"
	"5 9 8 3 7 4 1 6 2 \n"
	"7 6 4 1 2 9 5 3 8 \n"
	"8 7 1 2 9 6 3 4 5 \n"
	"2 5 6 7 4 3 8 9 1 \n"
	"3 4 9 5 8 1 7 2 6 \n"
	"9 1 5 4 3 2 6 8 7 \n"
	"4 2 7 6 5 8 9 1 3 \n"
	"6 8 3 9 1 7 2 5 4 \n"
	));
}

BOOST_AUTO_TEST_SUITE_END()

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