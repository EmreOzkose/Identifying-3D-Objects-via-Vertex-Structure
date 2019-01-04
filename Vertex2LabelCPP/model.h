using namespace std;

class Model {
	public:
		// Constructor
		Model(){
			// Weights
			vector<vector<float>> fc1_layer(hidden_layer_dim_1,	vector<float>(input_dim)); // Defaults to zero initial value
			vector<vector<float>> fc2_layer(hidden_layer_dim_2,	vector<float>(hidden_layer_dim_1)); // Defaults to zero initial value
			vector<vector<float>> fc3_layer(output_dim,	vector<float>(hidden_layer_dim_2)); // Defaults to zero initial value

			fc1 = fc1_layer;
			fc2 = fc2_layer;
			fc3 = fc3_layer;

		}


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
		vector<float> forward(vector<vector<float>> input[num_of_vertex]);


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


};

vector<float> Model::forward(vector<vector<float>> input[num_of_vertex]) {
	// First flatten the given vertex array (pytorch: view(.., -1))
	vector<float> *flattened = Model::flatten(*input);
	cout << "After flattened: " << flattened->size() << endl;

	vector<float> h1 = dotProduct(flattened, fc1);
	cout << "After dot product: " << h1.size() << endl;

	vector<float> z1 = ReLu(h1);
	cout << "After Relu: " << z1.size() << endl;

	vector<float> h2 = dotProduct(&z1, fc2);
	cout << "After 2. dot product: " << h2.size() << endl;

	vector<float> z2 = ReLu(h2);
	cout << "After 2. Relu: " << z2.size() << endl;

	vector<float> h3 = dotProduct(&z2, fc3);
	cout << "After 3. dot product: " << h3.size() << endl;

	return h3;

}

float Model::dotProductIn(vector<float> *input1, vector<float> input2) {
	float value = 0;
	for (int i = 0; i < input1->size(); i++) {
		value += input1->at(i) * input2.at(i);
	}

	return value;
}


vector<float> Model::dotProduct(vector<float> *vector1, vector<vector<float>> vector2) {
	vector<float> r;

	for (int i = 0; i < vector2.size(); i++)
		r.push_back(dotProductIn(vector1, vector2.at(i)));

	return r;
}


void Model::vec2float(vector<vector<float>> input) {

}

vector<float>* Model::flatten(vector<vector<float>> input) {

	vector<float> *flatten = new vector<float>;

	for (int i = 0; i < num_of_vertex; i++) {
		for (int j = 0; j < 3; j++) {
			flatten->push_back(input.at(i).at(j));
		}
	}
	return flatten;
}

inline vector<float> Model::ReLu(vector<float> x) {

	for (int i = 0; i <x.size(); i++)
		if (x.at(i) < 0.0)
			x.at(i) = 0.0;
	return x;
}