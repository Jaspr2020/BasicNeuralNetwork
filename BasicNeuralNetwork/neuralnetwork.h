#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "Matrix.h"
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;

class NeuralNetwork {
public:
	NeuralNetwork(vector<int> layer_sizes);
	Matrix predict(Matrix a);
	void trainSGD(vector<vector<vector<double>>> trainingImages, vector<Matrix> trainingLabels, int epochs, int batchSize, double learningRate);
	void updateBatch(vector<pair<vector<vector<double>>, Matrix>> &batch, double learningRate);
	vector<vector<Matrix>> backPropagation(vector<vector<double>> &sample, Matrix &label);
private:
	vector<Matrix> weights;
	vector<Matrix> biases;

	Matrix Activation(Matrix x);
};

#endif