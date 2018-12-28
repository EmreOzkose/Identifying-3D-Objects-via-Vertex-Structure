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
	float* forward(vector<vector<float>> input[num_of_vertex]) {

		// First flatten the given vertex array (pytorch: view(.., -1))
		vector<float> *flattened = flatten(*input);

		// Start forward pass
		vector<float> *h = ReLu(flattened, num_of_vertex * 3);



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
	void vec2float(vector<vector<float>> input) {

	}

	/*
		Neural Networks take flatten vector of the objects.
		input  : vector of size (mxn)
		return : flatten object, vector of size (1xm*n)
	*/
	vector<float> *flatten(vector<vector<float>> input) {

		vector<float> *flatten = new vector<float>;

		for (int i = 0; i < num_of_vertex; i++) {
			for (int j = 0; j < 3; j++) {
				flatten->push_back(input.at(i).at(j));
			}
		}
		return flatten;
	}

	vector<float> *ReLu(vector<float> *x, int dim) {

		for (int i = 0; i < dim; i++)
			if (x->at(i) < 0.0)
				x->at(i) = 0.0;
		return x;
	}

};