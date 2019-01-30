#include "vtoL.h"
#include <limits>


void vtoL::forward(vector<vector<float>> input[num_of_vertex], vector<float> &probs)
{
	// First flatten the given vertex array (pytorch: view(.., -1))
	vector<float> *flattened = vtoL::flatten(*input);
	cout << "After flattened: " << flattened->size() << endl;

	// Normalize 
	float max_value = -numeric_limits<double>::infinity();
	for (int i = 0; i < 680 * 3; i++) {
		if (flattened->at(i) < 0) {
			if (max_value < -flattened->at(i))
				max_value = -flattened->at(i);
		}
		else {
			if (max_value < flattened->at(i))
				max_value = flattened->at(i);
		}
	}
	for (int i = 0; i < 680 * 3; i++)
		flattened->at(i) = flattened->at(i) / max_value;

	cout << "la" << endl;


	vector<float> hhelp1 = dotProduct(flattened, fc1), h1;
	for (size_t i = 0; i < hhelp1.size(); i++) {
		h1.push_back(hhelp1.at(i));
	}


	cout << "After dot product: " << h1.size() << endl;

	vector<float> z1 = ReLu(h1);
	cout << "After Relu: " << z1.size() << endl;


	vector<float> h2 = dotProduct(&z1, fc2);
	cout << "After 2. dot product: " << h2.size() << endl;

	vector<float> z2 = ReLu(h2);
	cout << "After 2. Relu: " << z2.size() << endl;

	vector<float> h3 = dotProduct(&z2, fc3);
	cout << "After 3. dot product: " << h3.size() << endl;


	for (size_t i = 0; i < outdim; i++)
	{
		probs.push_back(h3.at(i));
	}

}

float vtoL::dotProductIn(vector<float> *input1, vector<float> input2) {
	float value = 0;
	for (int i = 0; i < input1->size(); i++) {
		value += input1->at(i) * input2.at(i);
	}

	return value;
}

int vtoL::getClass(vector<float> probs) {
	std::vector<float>::iterator max_index_vec = max_element(probs.begin(), probs.end());
	int max_index = distance(probs.begin(), max_index_vec);
	return max_index;
}

vector<vector<float>> normalize(vector<vector<float>> in_vector) {
	cout << " " << endl;

	return in_vector;
}

vector<float> vtoL::dotProduct(vector<float> *vector1, vector<vector<float>> vector2) {
	vector<float> r;

	for (int i = 0; i < vector2.size(); i++)
		r.push_back(dotProductIn(vector1, vector2.at(i)));

	return r;
}


void vtoL::vec2float(vector<vector<float>> input) {

}

vector<float>* vtoL::flatten(vector<vector<float>> input) {

	vector<float> *flatten = new vector<float>;

	for (int i = 0; i < num_of_vertex; i++) {
		for (int j = 0; j < 3; j++) {
			flatten->push_back(input.at(i).at(j));
		}
	}
	return flatten;
}

inline vector<float> vtoL::ReLu(vector<float> x) {

	for (int i = 0; i < x.size(); i++)
		if (x.at(i) < 0.0)
			x.at(i) = 0.0;
	return x;
}