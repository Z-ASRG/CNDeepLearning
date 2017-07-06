#pragma once

#ifndef __FORWARDNEURALNETWORK_H__
#define __FORWARDNEURALNETWORK_H__

#include "NeuralLayer.h"

using namespace std;

namespace ASRG
{
	class ForwardNeuralNetwork
	{
	public:
		typedef vector<NeuralLayer*> Network;
	private:
		//Current network container
		Network m_Network;

		//Best network container
		Network m_OptimalNetwork;
	public:
		ForwardNeuralNetwork();
		~ForwardNeuralNetwork();

		//Add layer to network, will call ReshapeNetwork inside
		bool PushLayer(NeuralLayer* pLayer);

		//Insert layer to network, will call ReshapeNetwork inside
		bool InsertLayer(uint32 LayerID, NeuralLayer* pLayer);

		//Erase layer network, will call ReshapeNetwork inside
		bool EraseLayer(uint32 LayerID);

		//Reshape the input, output, batch size
		void ReshapeNetwork();

		//Forward, just call forward function in order
		void Forward(const Tensor &TrainingDataBatch);

		//Backward, call backward update grad, then use UpdateWeight function update weight
		void Backward(const Tensor &TrainingLabelBatch);

		//Training
		void Training(const vector<float32> &DataSet, const vector<float32> &LabelSet, float32 LearningRate, float32 Momentum, float32 Times);
	};
}

#endif