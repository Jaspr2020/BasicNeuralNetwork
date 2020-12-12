#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "Matrix.h"
#include <iostream>
#include <vector>
#include <string>
#include <math.h>

class NeuralNetwork {
public:
	NeuralNetwork(std::vector<int> layer_sizes);
	Matrix predict(Matrix a);
	void trainSGD(std::vector<std::vector<std::vector<double>>> trainingImages, std::vector<Matrix> trainingLabels, int epochs, int batchSize, double learningRate);
	void updateBatch(std::vector<std::pair<std::vector<std::vector<double>>, Matrix>> &batch, double learningRate);
	std::pair<std::vector<Matrix>, std::vector<Matrix>> backPropagation(std::vector<std::vector<double>> &sample, Matrix &label);
private:
	std::vector<Matrix> weights;
	std::vector<Matrix> biases;

	Matrix Activation(Matrix x);
};

#endif