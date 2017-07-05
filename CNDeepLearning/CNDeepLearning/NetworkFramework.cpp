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
	//test
	float inputdata[] = {0.05,0.10};
	Tensor input(inputdata,1,2);
	input.print();

	float h1weight[] = { 0.15,0.20,0.25,0.30 };
	Tensor h1_weight(h1weight,2,2);
	h1_weight.print();

	Tensor r = input*h1_weight;
	r.print();
	
}

void ASRG::NetworkFramework::run()
{

}

void ASRG::NetworkFramework::clear()
{

}
