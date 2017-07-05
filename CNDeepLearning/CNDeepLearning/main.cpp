#include<iostream>
#include "Tensor.h"

int main()
{
	using namespace ASRG;
	using namespace std;
	std::cout << "Hello! This is Puppy Test program!" << std::endl;

	try
	{
		Tensor tensor(2, 3, 4);
		tensor.print();

		tensor.setRandomsUniform();
		tensor.print();
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}


	system("pause");
	return 0;
}