#pragma once
#include <iostream>
#include "NetworkContext.h"
namespace ASRG
{
	class NetworkFramework
	{
	public:
		NetworkFramework();
		~NetworkFramework();
		void init();
		void run();
		void clear();

	protected:
		NetworkContext m_Context;
	};
}

