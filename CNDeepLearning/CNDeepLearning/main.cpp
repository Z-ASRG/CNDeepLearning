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
		float data[] = {0.95,0.76,0.33,0.5,0.2,0.3};
		Tensor t2(data,2,3);
		t2.print();
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}


	system("pause");
	return 0;
}