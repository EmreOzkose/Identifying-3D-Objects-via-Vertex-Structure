#include <stdlib.h>     /* atof */

using namespace std;

Model* read_weight_matrices(Model *model);

Model* read_weight_matrices(Model *model) {

	int i = 0, j = 0;
	string line;

	ifstream file1("fc1.out");
	while (getline(file1, line)) {
		model->fc1[i][j] = strtof((line).c_str(), 0);
		j++;

		if (j == input_dim) { j = 0; i++; }
	}

	i = 0; j = 0;
	ifstream file2("fc2.out");
	while (getline(file2, line)) {
		model->fc2[i][j] = strtof((line).c_str(), 0);
		j++;

		if (j == hidden_layer_dim_1) { j = 0; i++; }
	}

	i = 0; j = 0;
	ifstream file3("fc3.out");
	while (getline(file3, line)) {
		model->fc3[i][j] = strtof((line).c_str(), 0);
		j++;

		if (j == hidden_layer_dim_2) { j = 0; i++; }
	}

	return model;

}
