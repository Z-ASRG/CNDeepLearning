#include "NetworkContext.h"
#include <arrayfire.h>
using namespace ASRG;

NetworkContext::NetworkContext()
{
}


NetworkContext::~NetworkContext()
{
}

bool ASRG::NetworkContext::InitializeContext()
{
	af::setDevice(0);
	af::info();
	return true;
}
