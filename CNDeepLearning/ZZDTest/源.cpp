#include <iostream>
#include <boost/timer.hpp> 
#include <boost/compute.hpp>

using namespace std;
namespace compute = boost::compute;


BOOST_COMPUTE_FUNCTION(double, add_four, (double x),
{
	return x / 0.5;
});
double random(double start, double end)
{
	return  ((double)rand() / RAND_MAX)*(end - start) + start;
}
std::vector<double> idata;

int main()
{

	try
	{


		// get default device and setup context
		compute::device device = compute::system::default_device();
		compute::context context(device);
		compute::command_queue queue(context, device);

		for (int i = 0; i < 1000000; i++)
		{
			idata.push_back(random(0.01,0.99));
		}
		boost::timer timer;
		timer.elapsed();
		std::vector<double> cpudata(idata.size());
		for (int i = 0; i < 1000000; i++)
		{
			cpudata[i] =idata[i]/ 0.5;
		}
		cout << "normal time:" << timer.elapsed() << endl;

		boost::timer timergpu;

		compute::vector<double> gpudata(idata.size(),context);
		compute::vector<double> gpuresult(idata.size(), context);

		compute::copy(idata.begin(), idata.end(), gpudata.begin(), queue);

		compute::transform(gpudata.begin(), gpudata.end(), gpuresult.begin(), add_four, queue);

		std::vector<double> odata(idata.size());
		compute::copy(gpuresult.begin(), gpuresult.end(),odata.begin() ,queue);

		cout << "gpu time:" << timergpu.elapsed() << endl;

		//// point coordinates
		//float points[] = { 1.0f, 2.0f, 3.0f, 0.0f,
		//	-2.0f, -3.0f, 4.0f, 0.0f,
		//	1.0f, -2.0f, 2.5f, 0.0f,
		//	-7.0f, -3.0f, -2.0f, 0.0f,
		//	3.0f, 4.0f, -5.0f, 0.0f };

		//// create vector for five points
		//compute::vector<float4_> input(5, context);
		//compute::vector<float4_> output(5, context);
		//// copy point data to the device
		//compute::copy(
		//	reinterpret_cast<float4_ *>(points),
		//	reinterpret_cast<float4_ *>(points) + 5,
		//	input.begin(),
		//	queue
		//);

		//// calculate sum


		//boost::compute::transform(input.begin(), input.end(), input.begin(), add_four, queue);


		//std::vector<float4_> hostvv(5);
		//compute::copy(input.begin(), input.end(), hostvv.begin(), queue);
		cout << endl;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
	return 0;
}