#include "neuralnetwork.h"

//std::string toString(std::vector<int> v);
//std::string toString(std::vector<double> v);
//std::string toString(std::vector<std::vector<int>> v);
//std::string toString(std::vector<std::vector<double>> v);
//std::string toString(std::vector<Matrix> v);

namespace printing {

	//Returns a string holding the vector of integers 
	std::string toString(std::vector<int> v) {
		std::string str = "";
		for (unsigned int i = 0; i < v.size(); i++)
			str += (i == 0 ? "(" : "") + std::to_string(v.at(i)) + (i == v.size() - 1 ? ")" : ", ");
		return str;
	}

	//Returns a string holding the vector of doubles 
	std::string toString(std::vector<double> v) {
		std::string str = "";
		for (unsigned int i = 0; i < v.size(); i++)
			str += (i == 0 ? "(" : "") + std::to_string(v.at(i)) + (i == v.size() - 1 ? ")" : ", ");
		return str;
	}

	//Returns a string holding the 2D vector of integers 
	std::string toString(std::vector<std::vector<int>> v) {
		std::string str = "";
		for (unsigned int i = 0; i < v.size(); i++)
			str += (i == 0 ? "[" : "") + toString(v.at(i)) + (i == v.size() - 1 ? "]" : ", ");
		return str;
	}

	//Returns a string holding the 2D vector of doubles 
	std::string toString(std::vector<std::vector<double>> v) {
		std::string str = "";
		for (unsigned int i = 0; i < v.size(); i++)
			str += (i == 0 ? "[" : "") + toString(v.at(i)) + (i == v.size() - 1 ? "]" : ", ");
		return str;
	}

	//Returns a string holding the vector of matrices 
	std::string toString(std::vector<Matrix> v) {
		std::string str = "";
		for (unsigned int i = 0; i < v.size(); i++)
			str += v.at(i).ToString() + '\n' + (i == v.size() - 1 ? ' ' : '\n');
		return str;
	}

}

int main() {
	std::vector<int> layer_sizes{ 2, 5, 10 };
	Matrix x(layer_sizes[0], 1, 1);
	NeuralNetwork net(layer_sizes);
	//Matrix prediction = net.predict(x);

	std::vector<std::vector<std::vector<double>>> trainingImages;
	for (int i = 0; i < 10; i++) {
		std::vector<std::vector<double>> v2d;
		for (int j = 0; j < 10; j++) {
			std::vector<double> v;
			for (int k = 0; k < 10; k++) {
				v.push_back(i+j+k);
			}
			v2d.push_back(v);
		}
		trainingImages.push_back(v2d);
	}
	//string str = "(";
	//for (int k = 0; k < trainingImages.size(); k++) {
	//	//str += "(";
	//	for (unsigned int l = 0; l < trainingImages.at(k).size(); l++) {
	//		str += (l == 0 ? "[" : " ");
	//		for (unsigned int m = 0; m < trainingImages.at(k).at(l).size(); m++) {
	//			str += (m == 0 ? "[" : "") + to_string(trainingImages.at(k).at(l).at(m)) + (m == trainingImages.at(k).at(l).size() - 1 ? "]" : " ");
	//		}
	//		str += (l == trainingImages.at(k).size() - 1 ? "]" : "\n");
	//	}
	//	if(k != trainingImages.size() - 1) str += "\n\n";
	//}
	//str += ")";
	//cout << str << endl;

	std::vector<Matrix> trainingLabels;
	for (int i = 0; i < 10; i++) {
		Matrix m(10, 1, 0, 1);
		trainingLabels.push_back(m);
	}
	//string str2 = "(";
	//for (int i = 0; i < trainingLabels.size(); i++) {
	//	str2 += trainingLabels.at(i).ToString();
	//	if (i != trainingLabels.size() - 1) str2 += "\n\n";
	//}
	//str2 += ")";
	//cout << str2 << endl;


	net.trainSGD(trainingImages, trainingLabels, 2, 10, 4.0);

	//cout << prediction.ToString() << endl;

	return 0;
}