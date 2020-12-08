#include "neuralnetwork.h"

NeuralNetwork::NeuralNetwork(vector<int> layer_sizes) {
	vector<vector<int>> weight_shapes;
	//Fill weight_shapes
	for (int i = 1; i < layer_sizes.size(); i++) {
		vector<int> v{ layer_sizes[i], layer_sizes[i - 1] };
		weight_shapes.push_back(v);
	}
	//Fill weights
	for (unsigned int i = 0; i < weight_shapes.size(); i++) {
		//Add a matrix of the correct shape and fill it with a normal distribution (mean of 0 and deviation of 3)
		Matrix m(weight_shapes.at(i).at(0), weight_shapes.at(i).at(1), 0, 3);
		//Scale the weights relative to the inputs (smaller inputs make learning faster)
		m /= pow(weight_shapes.at(i).at(0), .5);
		weights.push_back(m);
	}
	//Fill biases
	for (unsigned int i = 1; i < layer_sizes.size(); i++) {
		Matrix m(layer_sizes.at(i), 1, 0);
		biases.push_back(m);
	}
}

Matrix NeuralNetwork::predict(Matrix a) {
	for (unsigned int i = 0; i < weights.size(); i++) {
		a = Activation(weights[i] * a + biases[i]);
	}
	return a;
}

void NeuralNetwork::trainSGD(vector<vector<vector<double>>> trainingImages, vector<Matrix> trainingLabels, int epochs, int batchSize, double learningRate) {
	/*
	Train using Stochastic Gradient Decent
	*/

	//Holds pairs of images (2d vectors) and labels (matrices)
	vector<pair<vector<vector<double>>, Matrix>> trainingData;
	for (unsigned int i = 0; i < trainingImages.size(); i++) {
		pair<vector<vector<double>>, Matrix> p;
		p = make_pair(trainingImages.at(i), trainingLabels.at(i));
		trainingData.push_back(p);
	}

	cout << "start training" << endl;
	for (int i = 0; i < epochs; i++) {
		vector<vector<pair<vector<vector<double>>, Matrix>>> batches;
		//It works I think?????
		for (unsigned int j = 0; j < trainingData.size(); j += batchSize) {
			vector<pair<vector<vector<double>>, Matrix>> p;
			for (unsigned int k = j; k < trainingData.size(); k++) {
				p.push_back(trainingData.at(k));
			}
			batches.push_back(p);
		}

		for (vector<pair<vector<vector<double>>, Matrix>> &batch : batches) {
			updateBatch(batch, learningRate);
		}

		cout << "epoch " << i << " complete" << endl;
	}
}

void NeuralNetwork::updateBatch(vector<pair<vector<vector<double>>, Matrix>> &batch, double learningRate) {
	/*
		Calculate direction of gradient given a batch,
		and apply the change to the weights and biases
	*/
	//these arrays hold the change in direction for each weight and bias
	vector<Matrix> biasGradients;
	vector<Matrix> weightGradients;
	for (unsigned int i = 0; i < biases.size(); i++) {
		//Matrices of the sizes of the bias and weight matrices filled with zeros
		Matrix biasGradient(biases[i].GetShape().first, biases[i].GetShape().second);
		Matrix weightGradient(weights[i].GetShape().first, weights[i].GetShape().second);
		biasGradients.push_back(biasGradient);
		weightGradients.push_back(weightGradient);
	}

	for (unsigned int i = 0; i < batch.size(); i++) {
		//calculate the direction of the gradient for a single sample
		vector<vector<Matrix>> backProp = backPropagation(batch.at(i).first, batch.at(i).second);
		vector<Matrix> biasDeltas = backProp[0];
		vector<Matrix> weightDeltas = backProp[1];

		//combine the result with results from previous samples
		for (unsigned int j = 0; j < biasGradients.size(); j++) {
			biasGradients[j] += biasDeltas[j];
			weightGradients[j] += weightDeltas[j];
		}
	}

	//apply the found gradient to the weights and biases using learning_rate and batch size
	for (unsigned int i = 0; i < biases.size(); i++) {
		biases[i] = biases[i] - (biasGradients[i] * (learningRate / batch.size()));
		weights[i] = weights[i] - (weightGradients[i] * (learningRate / batch.size()));
	}
}

vector<vector<Matrix>> NeuralNetwork::backPropagation(vector<vector<double>> &sample, Matrix &label)
{
	/*
		Feed a sample through the network and calculate the changes in weights and biases
		by propagating back through the network in such a way that the cost is minimized
	*/

	return vector<vector<Matrix>>();
}

Matrix NeuralNetwork::Activation(Matrix x) {
	Matrix temp = x;
	for (vector<double> &row : temp.GetData()) {
		for (double &value : row) {
			value = 1 / (1 + exp(-value));
		}
	}
	return temp;
}