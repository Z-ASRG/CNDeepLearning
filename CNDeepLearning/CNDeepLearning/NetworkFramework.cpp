#include "NetworkFramework.h"


using namespace ASRG;
inline void expandTensor(af::array& arr)
{
	float* m = arr.host<float>();
	float a[] = { m[0],m[0],m[1],m[1] };
	arr = af::array( 2, 2, a);
	delete[] m;
}

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
	float inputdata[] = { 0.05,0.10 };
	input = af::array( 1, 2, inputdata);

	float h1weight[] = { 0.15,0.20,0.25,0.30 };
	h1_weight = af::array( 2, 2, h1weight);

	float h2weight[] = { 0.40,0.45,0.50,0.55 };
	h2_weight = af::array( 2, 2, h2weight);

	float bv[] = { 0.35,0.35 };
	b = af::array( 1, 2, bv);

	float bv2[] = { 0.6,0.6 };
	b2 = af::array( 1, 2, bv2);

	float target[] = { 0.01,0.99 };
	Target = af::array(1, 2, target);

	learning_rate = 0.5;
}

void ASRG::NetworkFramework::run()
{
	int i = 10000;
	while (i > 0)
	{
		this->forward();
		this->backward();
		i--;
	}
	printf("\n\n\n E total %f\n", e_total);
	//this->test();
}

void ASRG::NetworkFramework::clear()
{

}

void ASRG::NetworkFramework::forward()
{
	//first level
	af::array neth = af::matmul(input,h1_weight);
	//af_print(neth);

	outh = neth + b;
	//af_print(outh);

	gfor(af::seq i, outh.dims(1))
	{
		outh(af::span, i) = 1.0 / (1.0 + exp(-1 * outh(af::span, i)));
	}
	//af_print(outh,10);

	//second level

	outo = af::matmul(outh, h2_weight)+ b2;
	//af_print(outh);
	//af_print(h2_weight);
	//af_print(outo);
	gfor(af::seq i, outo.dims(1))
	{
		outo(af::span, i) = 1.0 / (1.0 + exp(-1 * outo(af::span, i)));
	}

	af_print(outo);

	//get error


	E_total = Target - outo;
	
	gfor(af::seq i, E_total.dims(1))
	{
		E_total(af::span, i) = E_total(af::span, i)*E_total(af::span, i)*0.5;
	}
	//E_total.print();
	af_print(E_total);
	e_total = af::sum<float>(E_total);
	
}

void ASRG::NetworkFramework::backward()
{
	//BP
	af::array E_out = outo - Target;
	//cout << "!!!!!!!!!!!!!!" << endl;
	af_print(E_out);
	af::array  Out_net = (1 - outo);
	af_print(Out_net);
	gfor(af::seq i, Out_net.dims(1))
	{
		Out_net(af::span, i) = Out_net(af::span, i)*outo(af::span, i);
	}

	af_print(Out_net);

	af_print(outh);
	af::array  Net_w = outh;
	//Net_w.print();

	af::array  Ep = E_out;
	gfor(af::seq i, Ep.dims(1))
	{
		Ep(af::span, i) = Ep(af::span, i)
			*Out_net(af::span, i)
			*Net_w(af::span, i);
	}
	af_print(E_out);
	af_print(Out_net);
	af_print(Net_w); 
	
	expandTensor(Ep);

	//Ep.print();
	//h2_weight.print();

	af::array  weight_new = h2_weight - learning_rate*Ep;
	af_print(weight_new);
	//weight_new.print();
	af_print(Ep);
	af_print(h2_weight);
	//weight2

	af::array  net_o = E_out;
	gfor(af::seq i, net_o.dims(1))
	{
		net_o(af::span, i) = net_o(af::span, i)
			*Out_net(af::span, i);
	}
	expandTensor(net_o);
	//net_o.print();
	
	af::array  e_out = net_o;
	gfor(af::seq i, e_out.dims(1))
	{
		e_out(af::span, i) = e_out(af::span, i)
			*h2_weight(af::span, i);
	}
	af_print(e_out);
	//h2_weight.print();
	//e_out.print();
	float v[] = { 1,1 };
	af::array e_outh( 2, 1, v);
	af_print(e_outh);
	e_outh = af::matmul(e_out,e_outh);
	af_print(e_outh);
	//e_outh.print();
	af::array outh_neth = outh;
	
	gfor(af::seq i, outh_neth.dims(1))
	{
		outh_neth(af::span, i) = outh_neth(af::span, i)
			*(1 - outh_neth(af::span, i));
	}
	
	//outh_neth.print();
	e_outh = e_outh.T();
	af::array e_w = e_outh*outh_neth*input;
	
	//af_print(e_outh);
	//af_print(outh_neth);
	//af_print(input);
	//af_print(e_w,10);
	expandTensor(e_w );
	//e_w.print();

	af::array weight_new_1 = h1_weight - learning_rate*e_w;
	//weight_new_1.print();
	af_print(weight_new_1, 10);

	h1_weight = weight_new_1;
	h2_weight = weight_new;
}
void ASRG::NetworkFramework::test()
{
	//Initilizing Driver
	m_Context.InitializeContext();
	//test
	float inputdata[] = { 0.05,0.10 };
	Tensor input(inputdata, 1, 2);
	input.print();

	float h1weight[] = { 0.15,0.20,0.25,0.30 };
	Tensor h1_weight(h1weight, 2, 2);
	h1_weight.print();

	Tensor neth = input*h1_weight;
	neth.print();

	float bv[] = { 0.35,0.35 };
	Tensor b(bv, 1, 2);

	Tensor outh = neth + b;
	outh.print();

	gfor(af::seq i, outh.getDimensions(1))
	{
		outh.Array()(af::span, i) = 1.0 / (1.0 + exp(-1 * outh.Array()(af::span, i)));
	}
	outh.print();

	//second level
	float h2weight[] = { 0.40,0.45,0.50,0.55 };
	Tensor h2_weight(h2weight, 2, 2);

	float bv2[] = { 0.6,0.6 };
	Tensor b2(bv2, 1, 2);

	Tensor outo = outh*h2_weight + b2;
	gfor(af::seq i, outo.getDimensions(1))
	{
		outo.Array()(af::span, i) = 1.0 / (1.0 + exp(-1 * outo.Array()(af::span, i)));
	}

	outo.print();

	//get error
	float learning_rate = 0.5;

	float target[] = { 0.01,0.99 };
	Tensor Target(target, 1, 2);

	Tensor E_total = Target - outo;
	gfor(af::seq i, E_total.getDimensions(1))
	{
		E_total.Array()(af::span, i) = E_total.Array()(af::span, i)*E_total.Array()(af::span, i)*0.5;
	}
	E_total.print();

	float e_total = E_total.sumTensor();
	printf("\n\n\n E total %f\n", e_total);

	//BP
	Tensor E_out = outo - Target;
	E_out.print();
	Tensor Out_net = (1 - outo);

	gfor(af::seq i, Out_net.getDimensions(1))
	{
		Out_net.Array()(af::span, i) = Out_net.Array()(af::span, i)*outo.Array()(af::span, i);
	}

	Out_net.print();

	Tensor Net_w = outh;
	Net_w.print();

	Tensor Ep = E_out;
	gfor(af::seq i, Ep.getDimensions(1))
	{
		Ep.Array()(af::span, i) = Ep.Array()(af::span, i)
			*Out_net.Array()(af::span, i)
			*Net_w.Array()(af::span, i);
	}

	Ep = Ep.expandTensor();

	Ep.print();
	h2_weight.print();

	Tensor weight_new = h2_weight - learning_rate*Ep;

	weight_new.print();

	//hidden weight

	Tensor net_o = E_out;
	gfor(af::seq i, net_o.getDimensions(1))
	{
		net_o.Array()(af::span, i) = net_o.Array()(af::span, i)
			*Out_net.Array()(af::span, i);
	}
	net_o= net_o.expandTensor();
	net_o.print();

	Tensor e_out = net_o;
	gfor(af::seq i, e_out.getDimensions(1))
	{
		e_out.Array()(af::span, i) = e_out.Array()(af::span, i)
			*h2_weight.Array()(af::span, i);
	}
	h2_weight.print();
	e_out.print();
	float v[] = {1,1};
	Tensor e_outh(v,2,1);
	e_outh = e_out*e_outh;
	e_outh.print();
	Tensor outh_neth = outh;
	gfor(af::seq i, outh_neth.getDimensions(1))
	{
		outh_neth.Array()(af::span, i) = outh_neth.Array()(af::span, i)
			*(1- outh_neth.Array()(af::span, i));
	}
	outh_neth.print();
	e_outh = e_outh.tranverse();
	Tensor e_w = e_outh.multiply(outh_neth).multiply(input);
	e_w=e_w.expandTensor();
	e_w.print();

	Tensor weight_new_1 = h1_weight-learning_rate*e_w;
	weight_new_1.print();
}