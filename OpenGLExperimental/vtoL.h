#include <fstream>

#include "parameters.h"

#include <numeric>		// to calculate dot product, etc..
#include <vector>		// store weights

#include <iostream>
#include <functional>

#include <algorithm>

using namespace std;


class vtoL {
public:
	// Constructor

	int outdim = outdim;

	vtoL(int categorical) {
		if (categorical) {
			set_outdim(4);
		}
		else {
			set_outdim(20);
		}

		// Weights
		vector<vector<float>> fc1_layer(hidden_layer_dim_1, vector<float>(input_dim)); // Defaults to zero initial value
		vector<vector<float>> fc2_layer(hidden_layer_dim_2, vector<float>(hidden_layer_dim_1)); // Defaults to zero initial value
		vector<vector<float>> fc3_layer(outdim, vector<float>(hidden_layer_dim_2)); // Defaults to zero initial value

		fc1 = fc1_layer;
		fc2 = fc2_layer;
		fc3 = fc3_layer;

	}

	void set_outdim(int set) {
		outdim = set;
	}

	string index2label[20]{ "bear", "car", "cyborg", "deer", "dog",
		"elephant", "futcar", "goblin", "human", "lpcar", "monster_vehicle",
		"skeleton", "tree0", "tree1", "tree2", "tree3", "tree4", "vampire",
		"van", "wolf" };

	string index2label_category[4]{ "humanoid", "quadripedal", "tree", "vehicle" };


	// Weights
	vector<vector<float>> fc1;
	vector<vector<float>> fc2;
	vector<vector<float>> fc3;



	/*
		input: an object whose size is num_of_vertices sized x 4
		input type: vec4

		return : probabilities | size: output_dim x 1
		output type: float[]
	*/
	void forward(vector<vector<float>> input[num_of_vertex], vector<float> &probs);


	/*
		Since vertices consists of vec4 type arrays, converting them to float is necessary.
		input : vec4 vector
		return : float version of input
	*/
	void vec2float(vector<vector<float>> input);


	/*
		Neural Networks take flatten vector of the objects.
		input  : vector of size (mxn)
		return : flatten object, vector of size (1xm*n)
	*/
	vector<float> *flatten(vector<vector<float>> input);

	float dotProductIn(vector<float> *input1, vector<float> input2);


	vector<float> dotProduct(vector<float>* vector1, vector<vector<float>> vector2);


	vector<float> ReLu(vector<float> x);
	int getClass(vector<float> probs);
	vector<vector<float>> normalize(vector<vector<float>> in_vector);

};