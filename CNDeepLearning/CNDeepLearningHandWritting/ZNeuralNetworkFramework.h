#pragma once
#include <iostream>
#include<cmath>
#include <vector>
#include "Layer.h"
#include "HiddenLayer.h"
#include "OutputLayer.h"
#include "InputLayer.h"
#include "Tensor.h"
#include "ZUtil.h"

class ZNeuralNetworkFramework
{
public:
	ZNeuralNetworkFramework();
	~ZNeuralNetworkFramework();

public:
	virtual void init();
	virtual void run();
	virtual void end();

protected:


protected:
	InputLayer<double> input_layer;
	HiddenLayer<double> hidden_layer;
	OutputLayer<double> output_layer;
};

