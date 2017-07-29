#include <iostream>
#include<cmath>
#include <vector>
#include "ZNeuralNetworkFramework.h"


using namespace std;




int main()
{
	cout.precision(3);
	cout.setf(ios::fixed);
	cout << "ASRG ZZD CPU Multi-thread DNN" << endl;

	ZNeuralNetworkFramework frame;
	frame.init();
	frame.run();
	frame.end();


	return 0;
}