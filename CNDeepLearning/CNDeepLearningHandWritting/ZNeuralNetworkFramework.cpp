#include "ZNeuralNetworkFramework.h"
#include<boost/timer.hpp>
#include "Tensor.h"
#include "Database.h"



ZNeuralNetworkFramework::ZNeuralNetworkFramework()
	:input_layer(1,400),hidden_layer(1,11),output_layer(1,10)
{
}


ZNeuralNetworkFramework::~ZNeuralNetworkFramework()
{
}

void ZNeuralNetworkFramework::init()
{
	srand(unsigned(time(0)));

	std::string filepath = "G:\\train_image\\";

	std::vector<Tensor<double>> pic[10];
	readDataBase("0",filepath,pic[0]);
	/*readDataBase("1", filepath, pic[1]);
	readDataBase("2", filepath, pic[2]);
	readDataBase("3", filepath, pic[3]);
	readDataBase("4", filepath, pic[4]);
	readDataBase("5", filepath, pic[5]);
	readDataBase("6", filepath, pic[6]);
	readDataBase("7", filepath, pic[7]);
	readDataBase("8", filepath, pic[8]);
	readDataBase("9", filepath, pic[9]);*/



	double th[] = {0};
	double tb1[] = { 0};
	Tensor<double> i=pic[0][0], h(th, 1, 1), b1(tb1, 1, 1);

	i.reShape(1, i._shape.row*i._shape.column);
	input_layer.output_value = i;
	input_layer.child = &hidden_layer;

	h.generateRandomTensor(pic[0][0]._shape.row*pic[0][0]._shape.column,11);
	hidden_layer.weight = h;
	b1.generateRandomTensor(1,11);
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
	o.generateRandomTensor(11,10);
	output_layer.weight = o;
	b2.generateRandomTensor(1,10);
	output_layer.bias = b2;
	output_layer.target = target;
}

void ZNeuralNetworkFramework::run()
{
	boost::timer t;
	int i1 = 40000, k = 0;
	//int i1 = 9000000,k=0;
	int bg = 0;
	int i;
	double cerror;
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

		cerror = output_layer.getError();

	}
	
	cout << "Used time: " << t.elapsed() << endl;
	cout << "error:" << cerror << endl;

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
