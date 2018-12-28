#include <numeric>		// to calculate dot product, etc..
#include <vector>		// store weights

using namespace std;
// std::vector<std::array<float, 1000>> index(1000);
class Model {

public:
	// Parameters 
	static const int num_of_vertex = 680;
	static const int input_dim = num_of_vertex * 3;

	static const int num_of_hidden_layer = 2;
	static const int hidden_layer_dim_1 = 120;
	static const int hidden_layer_dim_2 = 84;
	static const int output_dim = 3;


	// Weights
	float fc1[input_dim][hidden_layer_dim_1] = { 0.0 };
	float fc2[hidden_layer_dim_1][hidden_layer_dim_2] = { 0.0 };
	float fc3[hidden_layer_dim_2][output_dim] = { 0.0 };


	/*
		input: an object whose size is num_of_vertices sized x 4
		input type: vec4

		return : probabilities | size: output_dim x 1
		output type: float[]
	*/
	float* forward(std::vector<float> input[num_of_vertex]) {

		std::vector<float> flattened = flatten(input);

		cout << flattened.size() << endl;


		float *probs = new float[output_dim];;
		probs[0] = 0.03;
		probs[1] = 0.2;
		probs[2] = 0.1;

		return probs;
	}

	/*
		Since vertices consists of vec4 type arrays, converting them to float is necessary.
		input : vec4 vector
		return : float version of input
	*/
	void vec2float(std::vector<float> input) {

	}

	/*
		Neural Networks take flatten vector of the objects.
		input  : vector of size (mxn)
		return : flatten object, vector of size (1xm*n)
	*/
	std::vector<float> flatten(std::vector<float> input[num_of_vertex]) {

		std::vector<float> flatten = {};
		for (int i = 0; i < num_of_vertex; i++) {
			for (int j = 0; j < 3; j++) {
				cout << input[i].size() << endl;
				//cout << input[i].at(j) << endl;
				//flatten.push_back(input[i].at(j));
			}
		}
		return flatten;
	}

};