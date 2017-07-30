#include "ZNeuralNetworkFramework.h"



ZNeuralNetworkFramework::ZNeuralNetworkFramework()
	:input_layer(1,10),hidden_layer(1,3),output_layer(1,10)
{
}


ZNeuralNetworkFramework::~ZNeuralNetworkFramework()
{
}

void ZNeuralNetworkFramework::init()
{
	srand(unsigned(time(0)));

	double ti[] = { 1.0,0.0,0.0,0.0,0.0,
		            0.0,0.0,0.0,0.0,0.0};
	double th[] = {0};
	double tb1[] = { 0};
	Tensor<double> i(ti, 1, 10), h(th, 1, 1), b1(tb1, 1, 1);

	input_layer.output_value = i;
	input_layer.child = &hidden_layer;

	h.generateRandomTensor(10,3);
	hidden_layer.weight = h;
	b1.generateRandomTensor(1,3);
	hidden_layer.bias = b1;
	hidden_layer.parent = &input_layer;
	hidden_layer.child = &output_layer;

	double to[] = { 0};
	double tb2[] = { 0};
	Tensor<double> o(to, 1, 1), b2(tb2, 1, 1);
	double te[] = { 1.0,0.0,0.0,0.0,0.0,
		            0.0,0.0,0.0,0.0,0.0 };


	Tensor<double> target(te, 1, 10);

	output_layer.parent = &hidden_layer;
	o.generateRandomTensor(3,10);
	output_layer.weight = o;
	b2.generateRandomTensor(1,10);
	output_layer.bias = b2;
	output_layer.target = target;
}

void ZNeuralNetworkFramework::run()
{
	int i1 = 9000000,k=0;
	int bg = 0;
	int i;
	while (i1 > 0)
	{
		
		i = random(0, 9);
		k++;
		if (k == 10)
			k = 0;
		input_layer.output_value._data[bg] = 0;
		output_layer.target._data[bg] = 0;
		input_layer.output_value._data[k] = 1;
		output_layer.target._data[k] = 1;
		bg = k;

		//forward
		hidden_layer.forward();
		output_layer.forward();

		output_layer.caculateError();


		//backward 
		output_layer.backward();
		hidden_layer.backward();
		i1--;
		//il1.showInput();
		//il3.showError();
	}
	


}

void ZNeuralNetworkFramework::end()
{
	cout << "Trainning finished!" << endl;
	int k = 0;

	while (k != 100)
	{
		for (int i = 0; i < 10; i++)
		{
			input_layer.output_value._data[i] = 0;
			output_layer.target._data[i] = 0;
		}

		cin >> k;

		input_layer.output_value._data[k] = 1;
		output_layer.target._data[k] = 1;

		//forward
		hidden_layer.forward();
		output_layer.forward();

		output_layer.caculateError();


		input_layer.showInput();
		output_layer.showError();
	}

}
