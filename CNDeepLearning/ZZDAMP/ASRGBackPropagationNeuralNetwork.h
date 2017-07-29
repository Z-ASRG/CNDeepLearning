//#pragma once
//#include <amp.h>  
//#include <amp_math.h>
//#include <iostream>  
//#include "ZUtil.h"
//
//using namespace concurrency;
//using namespace  std;
//
//
//
//class ASRGBackPropagationNeuralNetwork
//{
//public:
//	ASRGBackPropagationNeuralNetwork();
//	~ASRGBackPropagationNeuralNetwork();
//
//	void forward()
//	{
//		array_view<float, 2> error(1, 2);
//
//		//first level
//		parallel_for_each(
//			product.extent,
//			[=](index<2> idx) restrict(amp) {
//			mat_multiplyFF(idx, product, input, h1);
//			addFF(idx, product, product, b1);
//			sigmoidFF(idx, product, product);
//
//			//product2
//			mat_multiplyFF(idx, product2, product, h2);
//			addFF(idx, product2, product2, b2);
//			sigmoidFF(idx, product2, product2);
//
//			//error
//			minusFF(idx, error, target, product2);
//			dotFF(idx, error, error, error);
//			dotFF(idx, error, error, 0.5);
//		});
//
//		product.synchronize();
//		product2.synchronize();
//		error.synchronize();
//
//		float sumerror = map_reduce(error);
//	}
//
//	void backward()
//	{
//		//backward
//		array_view<float, 2> error_total(1, 2);
//		array_view<float, 2> out_net(1, 2);
//		array_view<float, 2> tempd(1, 2);
//		parallel_for_each(
//			error_total.extent,
//			[=](index<2> idx) restrict(amp) {
//			minusFF(idx, error_total, product2, target);
//			minusFF(idx, out_net, 1, product2);
//			dotFF(idx, out_net, out_net, product2);
//			dotFF(idx, tempd, error_total, out_net);
//		});
//
//		array_view<float, 2> ep(2, 2);
//		array_view<float, 2> weight_new(2, 2);
//		parallel_for_each(
//			ep.extent,
//			[=](index<2> idx) restrict(amp) {
//			int row = idx[0];//[0]
//			int col = idx[1];//[0,1]
//
//			ep[idx] = tempd(0, col)*product(0, row);
//			weight_new[idx] = h2(row, col) - 0.5f*ep(row, col);
//		});
//		//print(error_total);
//		//print(out_net);
//		//print(product);
//		//print(ep);
//
//		//print(h2);
//		//print(ep);
//		//print(weight_new);
//		//cout << "||||||||||||" << endl;
//
//		//h1
//		array_view<float, 2> net_o(1, 2);
//		parallel_for_each(
//			net_o.extent,
//			[=](index<2> idx) restrict(amp) {
//			dotFF(idx, net_o, error_total, out_net);
//		});
//		array_view<float, 2> e_out(2, 2);
//		parallel_for_each(
//			e_out.extent,
//			[=](index<2> idx) restrict(amp) {
//			int row = idx[0];//[0]
//			int col = idx[1];//[0,1]
//
//			e_out[idx] = net_o(0, col)*h2(row, col);
//		});
//		//print(e_out);
//		float temp[] = { 1,1 };
//		array_view<float, 2>  e_outh(1, 2, temp);
//		array_view<float, 2> out_neth(1, 2);
//		array_view<float, 2> te_w(1, 2);
//		parallel_for_each(
//			e_out.extent,
//			[=](index<2> idx) restrict(amp) {
//			int row = idx[1];//[0]
//							 //int col = idx[1];
//			e_outh[idx] = e_out(row, 0) + e_out(row, 1);
//			minusFF(idx, out_neth, 1, product);
//			dotFF(idx, out_neth, product, out_neth);
//			dotFF(idx, te_w, e_outh, out_neth);
//		}
//		);
//		//print(product);
//
//
//		//print(out_neth);
//
//		array_view<float, 2> e_w(2, 2);
//		array_view<float, 2> weight_new2(2, 2);
//		parallel_for_each(
//			e_w.extent,
//			[=](index<2> idx) restrict(amp) {
//			int row = idx[0];//[0]
//			int col = idx[1];//[0,1]
//
//			e_w[idx] = te_w(0, col)*input(0, row);
//			weight_new2[idx] = h1(row, col) - 0.5f*e_w(row, col);
//
//		});
//		//print(e_w);
//		//print(h1);
//		//print(e_w);
//		print(weight_new2);
//	}
//
//private:
//	
//	array_view<float, 2> input;
//	array_view<float, 2> h1;
//	array_view<float, 2> h2;
//	array_view<float, 2> b1;
//	array_view<float, 2> b2;
//	array_view<float, 2> target;
//
//	float learning_r;
//
//	array_view<float, 2> product;
//	array_view<float, 2> product2;
//	
//};
//
