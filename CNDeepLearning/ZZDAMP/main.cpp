#include <amp.h>  
#include <amp_math.h>
#include <iostream>  
#include<boost/timer.hpp>
#include "ZUtil.h"
using namespace concurrency;
using namespace  std;

float inputdata[] = { 0.05f,0.10f };
//h1 h2
float h1weight[] = { 0.15f,0.25f,   //node1 to h
0.20f,0.30f }; //node2 to h
float h2weight[] = { 0.40f,0.50f,
0.45f,0.55f };

float bv1[] = { 0.35f,0.35f };
float bv2[] = { 0.6f,0.6f };
float targetb[] = { 0.01f,0.99f };
float learning_r = 0.5f;

float BPforward(concurrency::array<float, 2>& input,
	concurrency::array<float, 2>& target,
	concurrency::array<float, 2>& h1,
	concurrency::array<float, 2>& h2,
	concurrency::array<float, 2>& b1,
	concurrency::array<float, 2>& b2,
	concurrency::array<float, 2>& product, concurrency::array<float, 2>& product2)
{
	concurrency::array<float, 2> error(1, 2);

	//first level
	parallel_for_each(
		product.extent,
		[&](index<2> idx) restrict(amp) {
		mat_multiplyFF(idx, product, input, h1);
		addFF(idx, product, product, b1);
		sigmoidFF(idx, product, product);

		//product2
		mat_multiplyFF(idx, product2, product, h2);
		addFF(idx, product2, product2, b2);
		sigmoidFF(idx, product2, product2);

		//error
		minusFF(idx, error, target, product2);
		dotFF(idx, error, error, error);
		dotFF(idx, error, error, 0.5);
	});
	array_view<float, 2> te = error;
	float sumerror = map_reduce(te);
	//cout << "Error :" << sumerror << endl;
	return sumerror;
}

void BPbackward(concurrency::array<float, 2>& product, concurrency::array<float, 2>& product2,
	            concurrency::array<float, 2>& target, concurrency::array<float, 2>& h1,
	            concurrency::array<float, 2>& h2, concurrency::array<float, 2>& input)
{
	//backward
	concurrency::array<float, 2> error_total(1, 2);
	concurrency::array<float, 2> out_net(1, 2);
	concurrency::array<float, 2> tempd(1, 2);
	parallel_for_each(
		error_total.extent,
		[&](index<2> idx) restrict(amp) {
		minusFF(idx, error_total, product2, target);
		minusFF(idx, out_net, 1, product2);
		dotFF(idx, out_net, out_net, product2);
		dotFF(idx, tempd, error_total, out_net);
	});


	//h1
	concurrency::array<float, 2> net_o(1, 2);
	parallel_for_each(
		net_o.extent,
		[&](index<2> idx) restrict(amp) {
		dotFF(idx, net_o, error_total, out_net);
	});
	concurrency::array<float, 2> e_out(2, 2);
	parallel_for_each(
		e_out.extent,
		[&](index<2> idx) restrict(amp) {
		int row = idx[0];//[0]
		int col = idx[1];//[0,1]

		e_out[idx] = net_o(0, col)*h2(row, col);
	});
	//print(e_out);
	float temp[] = { 1,1 };
	concurrency::array<float, 2>  e_outh(1, 2, temp);
	concurrency::array<float, 2> out_neth(1, 2);
	concurrency::array<float, 2> te_w(1, 2);
	parallel_for_each(
		e_out.extent,
		[&](index<2> idx) restrict(amp) {
		int row = idx[1];//[0]
						 //int col = idx[1];
		e_outh[idx] = e_out(row, 0) + e_out(row, 1);
		minusFF(idx, out_neth, 1, product);
		dotFF(idx, out_neth, product, out_neth);
		dotFF(idx, te_w, e_outh, out_neth);
	}
	);

	concurrency::array<float, 2> ep(2, 2);
	concurrency::array<float, 2> weight_new(2, 2);
	concurrency::array<float, 2> e_w(2, 2);
	concurrency::array<float, 2> weight_new2(2, 2);

	parallel_for_each(
		ep.extent,
		[&](index<2> idx) restrict(amp) {
		int row = idx[0];//[0]
		int col = idx[1];//[0,1]

		ep[idx] = tempd(0, col)*product(0, row);
		weight_new[idx] = h2(row, col) - 0.5f*ep(row, col);

		e_w[idx] = te_w(0, col)*input(0, row);
		weight_new2[idx] = h1(row, col) - 0.5f*e_w(row, col);
	});

	h1 = weight_new2;
	h2 = weight_new;
}
void main() {
	cout.precision(8);
	cout.setf(ios::fixed);

	boost::timer t;

	concurrency::array<float, 2> input(1, 2, inputdata);
	concurrency::array<float, 2> h1(2, 2, h1weight);
	concurrency::array<float, 2> h2(2, 2, h2weight);
	concurrency::array<float, 2> b1(1, 2, bv1);
	concurrency::array<float, 2> b2(1, 2, bv2);
	concurrency::array<float, 2> target(1, 2, targetb);

	concurrency::array<float, 2> product(1, 2);
	concurrency::array<float, 2> product2(1, 2);
	int i = 10000;
	float sumerror = 0.0;
	while (i > 0)
	{
		sumerror = BPforward(input, target, h1, h2, b1, b2, product, product2);
		BPbackward(product, product2, target, h1, h2, input);
		//print(h1);
		//print(h2);
		i--;
	}
	cout << "Total Time: " << t.elapsed() << endl;
	cout << "Total Error: " << sumerror << endl;
	system("Pause");
}