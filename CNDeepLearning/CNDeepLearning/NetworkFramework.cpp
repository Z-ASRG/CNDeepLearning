#include "NetworkFramework.h"
#include "Tensor.h"

using namespace ASRG;

NetworkFramework::NetworkFramework()
{
	printf("ASRG Deep Learning Engine version 0.1...");
}


NetworkFramework::~NetworkFramework()
{
}

void ASRG::NetworkFramework::init()
{
	//Initilizing Driver
	m_Context.InitializeContext();

	Tensor tensor(2, 3, 4);
	tensor.print();

	tensor.setRandomsUniform();
	tensor.print();
	float data[] = { 0.95,0.76,0.33,0.5,0.2,0.3 };
	Tensor t2(data, 2, 3);
	t2.print();
}

void ASRG::NetworkFramework::run()
{

}

void ASRG::NetworkFramework::clear()
{

}
