#include<iostream>
#include "NetworkFramework.h"

int main()
{
	using namespace ASRG;
	using namespace std;
	try
	{

		NetworkFramework framework;
		framework.init();
		framework.run();
		framework.clear();


	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}


	system("pause");
	return 0;
}