#include <stdlib.h>     /* atof */

using namespace std;


vtoL* read_weight_matrices(vtoL *model, int choice) {

	ifstream file1("Weights/each/fc1.out");
	ifstream file2("Weights/each/fc2.out");
	ifstream file3("Weights/each/fc3.out");


	ifstream file4("Weights/categorical/categorical_fc1.out");
	ifstream file5("Weights/categorical/categorical_fc2.out");
	ifstream file6("Weights/categorical/categorical_fc3.out");


	if (choice) {
		int i = 0, j = 0;
		string line;


		while (getline(file4, line)) {
			model->fc1[i][j] = strtof((line).c_str(), 0);
			j++;

			if (j == input_dim) { j = 0; i++; }
		}

		i = 0; j = 0;

		while (getline(file5, line)) {
			model->fc2[i][j] = strtof((line).c_str(), 0);
			j++;

			if (j == hidden_layer_dim_1) { j = 0; i++; }
		}

		i = 0; j = 0;

		cout << "size1: " << model->fc3.size() << " ";
		cout << "size2: " << model->fc3.at(0).size() << endl;

		while (getline(file6, line)) {
			model->fc3[i][j] = strtof((line).c_str(), 0);
			j++;

			if (j == hidden_layer_dim_2) { j = 0; i++; }
		}
	}
	else {
		int i = 0, j = 0;
		string line;


		while (getline(file1, line)) {
			model->fc1[i][j] = strtof((line).c_str(), 0);
			j++;

			if (j == input_dim) { j = 0; i++; }
		}

		i = 0; j = 0;

		while (getline(file2, line)) {
			model->fc2[i][j] = strtof((line).c_str(), 0);
			j++;

			if (j == hidden_layer_dim_1) { j = 0; i++; }
		}

		i = 0; j = 0;

		cout << "size1: " << model->fc3.size() << " ";
		cout << "size2: " << model->fc3.at(0).size() << endl;

		while (getline(file3, line)) {
			model->fc3[i][j] = strtof((line).c_str(), 0);
			j++;

			if (j == hidden_layer_dim_2) { j = 0; i++; }
		}
	}
	return model;

}