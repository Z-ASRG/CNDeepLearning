#include <iostream>
#include <boost/timer.hpp> 
#include <boost/compute.hpp>
#include <boost/bind.hpp>

using namespace std;
namespace compute = boost::compute;


class tt
{
public:
	void run()
	{
		boost::bind(&tt::test,this, 1020)();
	}
private:
	void test(int i)
	{
		cout << "@!#$" << i << endl;
	}
};

int main()
{

	try
	{
		
		tt t;
		t.run();
		
		cout << endl;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
	return 0;
}