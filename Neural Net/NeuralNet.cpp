#include <iostream>
#include "NeuralNet.h"
#include <vector>
#include <random>

using namespace std;



Neuron::Neuron(int nI) : numInputs(nI+1){


	for(int i=0; i < nI+1; ++i){

		//Set up with random Weight values

		vecWeight.push_back(RandomClamped());

	}
}


NeuronLayer::NeuronLayer(int nNurons, int numInputsPerNeuron) : numNeurons(numNeurons){


	for(int i = 0; i < nNurons; ++i){

		//Call Constructor for each Neuron
		
		vecNeurons.push_back(Neuron(numInputsPerNeuron));
	}
}